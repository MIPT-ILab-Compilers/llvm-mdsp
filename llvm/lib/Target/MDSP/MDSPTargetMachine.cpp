//===-- MDSPTargetMachine.cpp - Define TargetMachine for MDSP -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "MDSP.h"
#include "MDSPMCAsmInfo.h"
#include "MDSPTargetMachine.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetRegistry.h"

using namespace llvm;

extern "C" void LLVMInitializeMDSPTarget()
{
  // Register the target.
  RegisterTargetMachine <MDSPTargetMachine> X(TheMDSPTarget);
  RegisterAsmInfo<MDSPELFMCAsmInfo> A(TheMDSPTarget);
}

/// MDSPTargetMachine ctor - Create an ILP32 architecture model

MDSPTargetMachine::MDSPTargetMachine (const Target &T, const std::string &TT, 
        const std::string &FS)
  :   LLVMTargetMachine(T, TT),
      DataLayout			("e-P:32:32-F128:128:128"), 
      TLInfo(*this), TSInfo(*this), InstrInfo(*this), FrameLowering(*this) {
}

bool MDSPTargetMachine::addInstSelector(PassManagerBase &PM,
                                         CodeGenOpt::Level OptLevel) {
  PM.add(createMDSPISelDag(*this));
  return false;
}

/// addPreEmitPass - This pass may be implemented by targets that want to run
/// passes immediately before machine code is emitted.  This should return
/// true if -print-machineinstrs should print out the code after the passes.
bool MDSPTargetMachine::addPreEmitPass(PassManagerBase &PM,
                                        CodeGenOpt::Level OptLevel){
  return true;
}
