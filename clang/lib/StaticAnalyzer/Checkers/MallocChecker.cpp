//=== MallocChecker.cpp - A malloc/free checker -------------------*- C++ -*--//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines malloc/free checker, which checks for potential memory
// leaks, double free, and use-after-free problems.
//
//===----------------------------------------------------------------------===//

#include "ClangSACheckers.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/CheckerManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/GRState.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/GRStateTrait.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/SymbolManager.h"
#include "llvm/ADT/ImmutableMap.h"
using namespace clang;
using namespace ento;

namespace {

class RefState {
  enum Kind { AllocateUnchecked, AllocateFailed, Released, Escaped,
              Relinquished } K;
  const Stmt *S;

public:
  RefState(Kind k, const Stmt *s) : K(k), S(s) {}

  bool isAllocated() const { return K == AllocateUnchecked; }
  //bool isFailed() const { return K == AllocateFailed; }
  bool isReleased() const { return K == Released; }
  //bool isEscaped() const { return K == Escaped; }
  //bool isRelinquished() const { return K == Relinquished; }

  bool operator==(const RefState &X) const {
    return K == X.K && S == X.S;
  }

  static RefState getAllocateUnchecked(const Stmt *s) { 
    return RefState(AllocateUnchecked, s); 
  }
  static RefState getAllocateFailed() {
    return RefState(AllocateFailed, 0);
  }
  static RefState getReleased(const Stmt *s) { return RefState(Released, s); }
  static RefState getEscaped(const Stmt *s) { return RefState(Escaped, s); }
  static RefState getRelinquished(const Stmt *s) {
    return RefState(Relinquished, s);
  }

  void Profile(llvm::FoldingSetNodeID &ID) const {
    ID.AddInteger(K);
    ID.AddPointer(S);
  }
};

class RegionState {};

class MallocChecker : public Checker<eval::Call, check::DeadSymbols, check::EndPath, check::PreStmt<ReturnStmt>, check::Location,
                               check::Bind, eval::Assume> {
  mutable llvm::OwningPtr<BuiltinBug> BT_DoubleFree;
  mutable llvm::OwningPtr<BuiltinBug> BT_Leak;
  mutable llvm::OwningPtr<BuiltinBug> BT_UseFree;
  mutable llvm::OwningPtr<BuiltinBug> BT_UseRelinquished;
  mutable llvm::OwningPtr<BuiltinBug> BT_BadFree;
  mutable IdentifierInfo *II_malloc, *II_free, *II_realloc, *II_calloc;

public:
  MallocChecker() : II_malloc(0), II_free(0), II_realloc(0), II_calloc(0) {}

  bool evalCall(const CallExpr *CE, CheckerContext &C) const;
  void checkDeadSymbols(SymbolReaper &SymReaper, CheckerContext &C) const;
  void checkEndPath(EndOfFunctionNodeBuilder &B, ExprEngine &Eng) const;
  void checkPreStmt(const ReturnStmt *S, CheckerContext &C) const;
  const GRState *evalAssume(const GRState *state, SVal Cond,
                            bool Assumption) const;
  void checkLocation(SVal l, bool isLoad, CheckerContext &C) const;
  void checkBind(SVal location, SVal val, CheckerContext &C) const;

private:
  static void MallocMem(CheckerContext &C, const CallExpr *CE);
  static void MallocMemReturnsAttr(CheckerContext &C, const CallExpr *CE,
                                   const OwnershipAttr* Att);
  static const GRState *MallocMemAux(CheckerContext &C, const CallExpr *CE,
                                     const Expr *SizeEx, SVal Init,
                                     const GRState *state) {
    return MallocMemAux(C, CE, state->getSVal(SizeEx), Init, state);
  }
  static const GRState *MallocMemAux(CheckerContext &C, const CallExpr *CE,
                                     SVal SizeEx, SVal Init,
                                     const GRState *state);

  void FreeMem(CheckerContext &C, const CallExpr *CE) const;
  void FreeMemAttr(CheckerContext &C, const CallExpr *CE,
                   const OwnershipAttr* Att) const;
  const GRState *FreeMemAux(CheckerContext &C, const CallExpr *CE,
                           const GRState *state, unsigned Num, bool Hold) const;

  void ReallocMem(CheckerContext &C, const CallExpr *CE) const;
  static void CallocMem(CheckerContext &C, const CallExpr *CE);
  
  static bool SummarizeValue(llvm::raw_ostream& os, SVal V);
  static bool SummarizeRegion(llvm::raw_ostream& os, const MemRegion *MR);
  void ReportBadFree(CheckerContext &C, SVal ArgVal, SourceRange range) const;
};
} // end anonymous namespace

typedef llvm::ImmutableMap<SymbolRef, RefState> RegionStateTy;

namespace clang {
namespace ento {
  template <>
  struct GRStateTrait<RegionState> 
    : public GRStatePartialTrait<RegionStateTy> {
    static void *GDMIndex() { static int x; return &x; }
  };
}
}

bool MallocChecker::evalCall(const CallExpr *CE, CheckerContext &C) const {
  const GRState *state = C.getState();
  const Expr *Callee = CE->getCallee();
  SVal L = state->getSVal(Callee);

  const FunctionDecl *FD = L.getAsFunctionDecl();
  if (!FD)
    return false;

  ASTContext &Ctx = C.getASTContext();
  if (!II_malloc)
    II_malloc = &Ctx.Idents.get("malloc");
  if (!II_free)
    II_free = &Ctx.Idents.get("free");
  if (!II_realloc)
    II_realloc = &Ctx.Idents.get("realloc");
  if (!II_calloc)
    II_calloc = &Ctx.Idents.get("calloc");

  if (FD->getIdentifier() == II_malloc) {
    MallocMem(C, CE);
    return true;
  }

  if (FD->getIdentifier() == II_free) {
    FreeMem(C, CE);
    return true;
  }

  if (FD->getIdentifier() == II_realloc) {
    ReallocMem(C, CE);
    return true;
  }

  if (FD->getIdentifier() == II_calloc) {
    CallocMem(C, CE);
    return true;
  }

  // Check all the attributes, if there are any.
  // There can be multiple of these attributes.
  bool rv = false;
  if (FD->hasAttrs()) {
    for (specific_attr_iterator<OwnershipAttr>
                  i = FD->specific_attr_begin<OwnershipAttr>(),
                  e = FD->specific_attr_end<OwnershipAttr>();
         i != e; ++i) {
      switch ((*i)->getOwnKind()) {
      case OwnershipAttr::Returns: {
        MallocMemReturnsAttr(C, CE, *i);
        rv = true;
        break;
      }
      case OwnershipAttr::Takes:
      case OwnershipAttr::Holds: {
        FreeMemAttr(C, CE, *i);
        rv = true;
        break;
      }
      default:
        break;
      }
    }
  }
  return rv;
}

void MallocChecker::MallocMem(CheckerContext &C, const CallExpr *CE) {
  const GRState *state = MallocMemAux(C, CE, CE->getArg(0), UndefinedVal(),
                                      C.getState());
  C.addTransition(state);
}

void MallocChecker::MallocMemReturnsAttr(CheckerContext &C, const CallExpr *CE,
                                         const OwnershipAttr* Att) {
  if (Att->getModule() != "malloc")
    return;

  OwnershipAttr::args_iterator I = Att->args_begin(), E = Att->args_end();
  if (I != E) {
    const GRState *state =
        MallocMemAux(C, CE, CE->getArg(*I), UndefinedVal(), C.getState());
    C.addTransition(state);
    return;
  }
  const GRState *state = MallocMemAux(C, CE, UnknownVal(), UndefinedVal(),
                                        C.getState());
  C.addTransition(state);
}

const GRState *MallocChecker::MallocMemAux(CheckerContext &C,  
                                           const CallExpr *CE,
                                           SVal Size, SVal Init,
                                           const GRState *state) {
  unsigned Count = C.getNodeBuilder().getCurrentBlockCount();
  SValBuilder &svalBuilder = C.getSValBuilder();

  // Set the return value.
  SVal retVal = svalBuilder.getConjuredSymbolVal(NULL, CE, CE->getType(), Count);
  state = state->BindExpr(CE, retVal);

  // Fill the region with the initialization value.
  state = state->bindDefault(retVal, Init);

  // Set the region's extent equal to the Size parameter.
  const SymbolicRegion *R = cast<SymbolicRegion>(retVal.getAsRegion());
  DefinedOrUnknownSVal Extent = R->getExtent(svalBuilder);
  DefinedOrUnknownSVal DefinedSize = cast<DefinedOrUnknownSVal>(Size);
  DefinedOrUnknownSVal extentMatchesSize =
    svalBuilder.evalEQ(state, Extent, DefinedSize);

  state = state->assume(extentMatchesSize, true);
  assert(state);
  
  SymbolRef Sym = retVal.getAsLocSymbol();
  assert(Sym);

  // Set the symbol's state to Allocated.
  return state->set<RegionState>(Sym, RefState::getAllocateUnchecked(CE));
}

void MallocChecker::FreeMem(CheckerContext &C, const CallExpr *CE) const {
  const GRState *state = FreeMemAux(C, CE, C.getState(), 0, false);

  if (state)
    C.addTransition(state);
}

void MallocChecker::FreeMemAttr(CheckerContext &C, const CallExpr *CE,
                                const OwnershipAttr* Att) const {
  if (Att->getModule() != "malloc")
    return;

  for (OwnershipAttr::args_iterator I = Att->args_begin(), E = Att->args_end();
       I != E; ++I) {
    const GRState *state = FreeMemAux(C, CE, C.getState(), *I,
                                      Att->getOwnKind() == OwnershipAttr::Holds);
    if (state)
      C.addTransition(state);
  }
}

const GRState *MallocChecker::FreeMemAux(CheckerContext &C, const CallExpr *CE,
                                         const GRState *state, unsigned Num,
                                         bool Hold) const {
  const Expr *ArgExpr = CE->getArg(Num);
  SVal ArgVal = state->getSVal(ArgExpr);

  DefinedOrUnknownSVal location = cast<DefinedOrUnknownSVal>(ArgVal);

  // Check for null dereferences.
  if (!isa<Loc>(location))
    return state;

  // FIXME: Technically using 'Assume' here can result in a path
  //  bifurcation.  In such cases we need to return two states, not just one.
  const GRState *notNullState, *nullState;
  llvm::tie(notNullState, nullState) = state->assume(location);

  // The explicit NULL case, no operation is performed.
  if (nullState && !notNullState)
    return nullState;

  assert(notNullState);

  // Unknown values could easily be okay
  // Undefined values are handled elsewhere
  if (ArgVal.isUnknownOrUndef())
    return notNullState;

  const MemRegion *R = ArgVal.getAsRegion();
  
  // Nonlocs can't be freed, of course.
  // Non-region locations (labels and fixed addresses) also shouldn't be freed.
  if (!R) {
    ReportBadFree(C, ArgVal, ArgExpr->getSourceRange());
    return NULL;
  }
  
  R = R->StripCasts();
  
  // Blocks might show up as heap data, but should not be free()d
  if (isa<BlockDataRegion>(R)) {
    ReportBadFree(C, ArgVal, ArgExpr->getSourceRange());
    return NULL;
  }
  
  const MemSpaceRegion *MS = R->getMemorySpace();
  
  // Parameters, locals, statics, and globals shouldn't be freed.
  if (!(isa<UnknownSpaceRegion>(MS) || isa<HeapSpaceRegion>(MS))) {
    // FIXME: at the time this code was written, malloc() regions were
    // represented by conjured symbols, which are all in UnknownSpaceRegion.
    // This means that there isn't actually anything from HeapSpaceRegion
    // that should be freed, even though we allow it here.
    // Of course, free() can work on memory allocated outside the current
    // function, so UnknownSpaceRegion is always a possibility.
    // False negatives are better than false positives.
    
    ReportBadFree(C, ArgVal, ArgExpr->getSourceRange());
    return NULL;
  }
  
  const SymbolicRegion *SR = dyn_cast<SymbolicRegion>(R);
  // Various cases could lead to non-symbol values here.
  // For now, ignore them.
  if (!SR)
    return notNullState;

  SymbolRef Sym = SR->getSymbol();
  const RefState *RS = state->get<RegionState>(Sym);

  // If the symbol has not been tracked, return. This is possible when free() is
  // called on a pointer that does not get its pointee directly from malloc(). 
  // Full support of this requires inter-procedural analysis.
  if (!RS)
    return notNullState;

  // Check double free.
  if (RS->isReleased()) {
    if (ExplodedNode *N = C.generateSink()) {
      if (!BT_DoubleFree)
        BT_DoubleFree.reset(
          new BuiltinBug("Double free",
                         "Try to free a memory block that has been released"));
      // FIXME: should find where it's freed last time.
      BugReport *R = new BugReport(*BT_DoubleFree, 
                                   BT_DoubleFree->getDescription(), N);
      C.EmitReport(R);
    }
    return NULL;
  }

  // Normal free.
  if (Hold)
    return notNullState->set<RegionState>(Sym, RefState::getRelinquished(CE));
  return notNullState->set<RegionState>(Sym, RefState::getReleased(CE));
}

bool MallocChecker::SummarizeValue(llvm::raw_ostream& os, SVal V) {
  if (nonloc::ConcreteInt *IntVal = dyn_cast<nonloc::ConcreteInt>(&V))
    os << "an integer (" << IntVal->getValue() << ")";
  else if (loc::ConcreteInt *ConstAddr = dyn_cast<loc::ConcreteInt>(&V))
    os << "a constant address (" << ConstAddr->getValue() << ")";
  else if (loc::GotoLabel *Label = dyn_cast<loc::GotoLabel>(&V))
    os << "the address of the label '" << Label->getLabel()->getName() << "'";
  else
    return false;
  
  return true;
}

bool MallocChecker::SummarizeRegion(llvm::raw_ostream& os,
                                    const MemRegion *MR) {
  switch (MR->getKind()) {
  case MemRegion::FunctionTextRegionKind: {
    const FunctionDecl *FD = cast<FunctionTextRegion>(MR)->getDecl();
    if (FD)
      os << "the address of the function '" << FD << "'";
    else
      os << "the address of a function";
    return true;
  }
  case MemRegion::BlockTextRegionKind:
    os << "block text";
    return true;
  case MemRegion::BlockDataRegionKind:
    // FIXME: where the block came from?
    os << "a block";
    return true;
  default: {
    const MemSpaceRegion *MS = MR->getMemorySpace();
    
    switch (MS->getKind()) {
    case MemRegion::StackLocalsSpaceRegionKind: {
      const VarRegion *VR = dyn_cast<VarRegion>(MR);
      const VarDecl *VD;
      if (VR)
        VD = VR->getDecl();
      else
        VD = NULL;
      
      if (VD)
        os << "the address of the local variable '" << VD->getName() << "'";
      else
        os << "the address of a local stack variable";
      return true;
    }
    case MemRegion::StackArgumentsSpaceRegionKind: {
      const VarRegion *VR = dyn_cast<VarRegion>(MR);
      const VarDecl *VD;
      if (VR)
        VD = VR->getDecl();
      else
        VD = NULL;
      
      if (VD)
        os << "the address of the parameter '" << VD->getName() << "'";
      else
        os << "the address of a parameter";
      return true;
    }
    case MemRegion::NonStaticGlobalSpaceRegionKind:
    case MemRegion::StaticGlobalSpaceRegionKind: {
      const VarRegion *VR = dyn_cast<VarRegion>(MR);
      const VarDecl *VD;
      if (VR)
        VD = VR->getDecl();
      else
        VD = NULL;
      
      if (VD) {
        if (VD->isStaticLocal())
          os << "the address of the static variable '" << VD->getName() << "'";
        else
          os << "the address of the global variable '" << VD->getName() << "'";
      } else
        os << "the address of a global variable";
      return true;
    }
    default:
      return false;
    }
  }
  }
}

void MallocChecker::ReportBadFree(CheckerContext &C, SVal ArgVal,
                                  SourceRange range) const {
  if (ExplodedNode *N = C.generateSink()) {
    if (!BT_BadFree)
      BT_BadFree.reset(new BuiltinBug("Bad free"));
    
    llvm::SmallString<100> buf;
    llvm::raw_svector_ostream os(buf);
    
    const MemRegion *MR = ArgVal.getAsRegion();
    if (MR) {
      while (const ElementRegion *ER = dyn_cast<ElementRegion>(MR))
        MR = ER->getSuperRegion();
      
      // Special case for alloca()
      if (isa<AllocaRegion>(MR))
        os << "Argument to free() was allocated by alloca(), not malloc()";
      else {
        os << "Argument to free() is ";
        if (SummarizeRegion(os, MR))
          os << ", which is not memory allocated by malloc()";
        else
          os << "not memory allocated by malloc()";
      }
    } else {
      os << "Argument to free() is ";
      if (SummarizeValue(os, ArgVal))
        os << ", which is not memory allocated by malloc()";
      else
        os << "not memory allocated by malloc()";
    }
    
    EnhancedBugReport *R = new EnhancedBugReport(*BT_BadFree, os.str(), N);
    R->addRange(range);
    C.EmitReport(R);
  }
}

void MallocChecker::ReallocMem(CheckerContext &C, const CallExpr *CE) const {
  const GRState *state = C.getState();
  const Expr *arg0Expr = CE->getArg(0);
  DefinedOrUnknownSVal arg0Val 
    = cast<DefinedOrUnknownSVal>(state->getSVal(arg0Expr));

  SValBuilder &svalBuilder = C.getSValBuilder();

  DefinedOrUnknownSVal PtrEQ =
    svalBuilder.evalEQ(state, arg0Val, svalBuilder.makeNull());

  // If the ptr is NULL, the call is equivalent to malloc(size).
  if (const GRState *stateEqual = state->assume(PtrEQ, true)) {
    // Hack: set the NULL symbolic region to released to suppress false warning.
    // In the future we should add more states for allocated regions, e.g., 
    // CheckedNull, CheckedNonNull.
    
    SymbolRef Sym = arg0Val.getAsLocSymbol();
    if (Sym)
      stateEqual = stateEqual->set<RegionState>(Sym, RefState::getReleased(CE));

    const GRState *stateMalloc = MallocMemAux(C, CE, CE->getArg(1), 
                                              UndefinedVal(), stateEqual);
    C.addTransition(stateMalloc);
  }

  if (const GRState *stateNotEqual = state->assume(PtrEQ, false)) {
    const Expr *Arg1 = CE->getArg(1);
    DefinedOrUnknownSVal Arg1Val = 
      cast<DefinedOrUnknownSVal>(stateNotEqual->getSVal(Arg1));
    DefinedOrUnknownSVal SizeZero =
      svalBuilder.evalEQ(stateNotEqual, Arg1Val,
                         svalBuilder.makeIntValWithPtrWidth(0, false));

    if (const GRState *stateSizeZero = stateNotEqual->assume(SizeZero, true))
      if (const GRState *stateFree = FreeMemAux(C, CE, stateSizeZero, 0, false))
        C.addTransition(stateFree->BindExpr(CE, UndefinedVal(), true));

    if (const GRState *stateSizeNotZero = stateNotEqual->assume(SizeZero,false))
      if (const GRState *stateFree = FreeMemAux(C, CE, stateSizeNotZero,
                                                0, false)) {
        // FIXME: We should copy the content of the original buffer.
        const GRState *stateRealloc = MallocMemAux(C, CE, CE->getArg(1), 
                                                   UnknownVal(), stateFree);
        C.addTransition(stateRealloc);
      }
  }
}

void MallocChecker::CallocMem(CheckerContext &C, const CallExpr *CE) {
  const GRState *state = C.getState();
  SValBuilder &svalBuilder = C.getSValBuilder();

  SVal count = state->getSVal(CE->getArg(0));
  SVal elementSize = state->getSVal(CE->getArg(1));
  SVal TotalSize = svalBuilder.evalBinOp(state, BO_Mul, count, elementSize,
                                        svalBuilder.getContext().getSizeType());  
  SVal zeroVal = svalBuilder.makeZeroVal(svalBuilder.getContext().CharTy);

  C.addTransition(MallocMemAux(C, CE, TotalSize, zeroVal, state));
}

void MallocChecker::checkDeadSymbols(SymbolReaper &SymReaper,
                                     CheckerContext &C) const
{
  if (!SymReaper.hasDeadSymbols())
    return;

  const GRState *state = C.getState();
  RegionStateTy RS = state->get<RegionState>();
  RegionStateTy::Factory &F = state->get_context<RegionState>();

  for (RegionStateTy::iterator I = RS.begin(), E = RS.end(); I != E; ++I) {
    if (SymReaper.isDead(I->first)) {
      if (I->second.isAllocated()) {
        if (ExplodedNode *N = C.generateNode()) {
          if (!BT_Leak)
            BT_Leak.reset(new BuiltinBug("Memory leak",
                    "Allocated memory never released. Potential memory leak."));
          // FIXME: where it is allocated.
          BugReport *R = new BugReport(*BT_Leak, BT_Leak->getDescription(), N);
          C.EmitReport(R);
        }
      }

      // Remove the dead symbol from the map.
      RS = F.remove(RS, I->first);
    }
  }
  C.generateNode(state->set<RegionState>(RS));
}

void MallocChecker::checkEndPath(EndOfFunctionNodeBuilder &B,
                                 ExprEngine &Eng) const {
  const GRState *state = B.getState();
  RegionStateTy M = state->get<RegionState>();

  for (RegionStateTy::iterator I = M.begin(), E = M.end(); I != E; ++I) {
    RefState RS = I->second;
    if (RS.isAllocated()) {
      ExplodedNode *N = B.generateNode(state);
      if (N) {
        if (!BT_Leak)
          BT_Leak.reset(new BuiltinBug("Memory leak",
                    "Allocated memory never released. Potential memory leak."));
        BugReport *R = new BugReport(*BT_Leak, BT_Leak->getDescription(), N);
        Eng.getBugReporter().EmitReport(R);
      }
    }
  }
}

void MallocChecker::checkPreStmt(const ReturnStmt *S, CheckerContext &C) const {
  const Expr *retExpr = S->getRetValue();
  if (!retExpr)
    return;

  const GRState *state = C.getState();

  SymbolRef Sym = state->getSVal(retExpr).getAsSymbol();
  if (!Sym)
    return;

  const RefState *RS = state->get<RegionState>(Sym);
  if (!RS)
    return;

  // FIXME: check other cases.
  if (RS->isAllocated())
    state = state->set<RegionState>(Sym, RefState::getEscaped(S));

  C.addTransition(state);
}

const GRState *MallocChecker::evalAssume(const GRState *state, SVal Cond, 
                                         bool Assumption) const {
  // If a symblic region is assumed to NULL, set its state to AllocateFailed.
  // FIXME: should also check symbols assumed to non-null.

  RegionStateTy RS = state->get<RegionState>();

  for (RegionStateTy::iterator I = RS.begin(), E = RS.end(); I != E; ++I) {
    if (state->getSymVal(I.getKey()))
      state = state->set<RegionState>(I.getKey(),RefState::getAllocateFailed());
  }

  return state;
}

// Check if the location is a freed symbolic region.
void MallocChecker::checkLocation(SVal l, bool isLoad,CheckerContext &C) const {
  SymbolRef Sym = l.getLocSymbolInBase();
  if (Sym) {
    const RefState *RS = C.getState()->get<RegionState>(Sym);
    if (RS && RS->isReleased()) {
      if (ExplodedNode *N = C.generateNode()) {
        if (!BT_UseFree)
          BT_UseFree.reset(new BuiltinBug("Use dynamically allocated memory "
                                          "after it is freed."));

        BugReport *R = new BugReport(*BT_UseFree, BT_UseFree->getDescription(),
                                     N);
        C.EmitReport(R);
      }
    }
  }
}

void MallocChecker::checkBind(SVal location, SVal val,CheckerContext &C) const {
  // The PreVisitBind implements the same algorithm as already used by the 
  // Objective C ownership checker: if the pointer escaped from this scope by 
  // assignment, let it go.  However, assigning to fields of a stack-storage 
  // structure does not transfer ownership.

  const GRState *state = C.getState();
  DefinedOrUnknownSVal l = cast<DefinedOrUnknownSVal>(location);

  // Check for null dereferences.
  if (!isa<Loc>(l))
    return;

  // Before checking if the state is null, check if 'val' has a RefState.
  // Only then should we check for null and bifurcate the state.
  SymbolRef Sym = val.getLocSymbolInBase();
  if (Sym) {
    if (const RefState *RS = state->get<RegionState>(Sym)) {
      // If ptr is NULL, no operation is performed.
      const GRState *notNullState, *nullState;
      llvm::tie(notNullState, nullState) = state->assume(l);

      // Generate a transition for 'nullState' to record the assumption
      // that the state was null.
      if (nullState)
        C.addTransition(nullState);

      if (!notNullState)
        return;

      if (RS->isAllocated()) {
        // Something we presently own is being assigned somewhere.
        const MemRegion *AR = location.getAsRegion();
        if (!AR)
          return;
        AR = AR->StripCasts()->getBaseRegion();
        do {
          // If it is on the stack, we still own it.
          if (AR->hasStackNonParametersStorage())
            break;

          // If the state can't represent this binding, we still own it.
          if (notNullState == (notNullState->bindLoc(cast<Loc>(location),
                                                     UnknownVal())))
            break;

          // We no longer own this pointer.
          notNullState =
            notNullState->set<RegionState>(Sym,
                                        RefState::getRelinquished(C.getStmt()));
        }
        while (false);
      }
      C.addTransition(notNullState);
    }
  }
}

void ento::registerMallocChecker(CheckerManager &mgr) {
  mgr.registerChecker<MallocChecker>();
}
