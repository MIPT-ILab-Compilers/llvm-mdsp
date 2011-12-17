//===-- MDSPISelLowering.h - MDSP DAG Lowering Interface --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that MDSP uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPISELLOWERING_H
#define MDSPISELLOWERING_H

#include "llvm/Target/TargetLowering.h"
#include "MDSP.h"

namespace llvm {

  class MDSPTargetLowering : public TargetLowering {
  public:
    MDSPTargetLowering(TargetMachine &TM);
/*
    virtual SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const;

    /// computeMaskedBitsForTargetNode - Determine which of the bits specified
    /// in Mask are known to be either zero or one and return them in the
    /// KnownZero/KnownOne bitsets.
    virtual void computeMaskedBitsForTargetNode(const SDValue Op,
                                                const APInt &Mask,
                                                APInt &KnownZero,
                                                APInt &KnownOne,
                                                const SelectionDAG &DAG,
                                                unsigned Depth = 0) const;

    virtual MachineBasicBlock *
      EmitInstrWithCustomInserter(MachineInstr *MI,
                                  MachineBasicBlock *MBB) const;

    virtual const char *getTargetNodeName(unsigned Opcode) const;

    ConstraintType getConstraintType(const std::string &Constraint) const;
    std::pair<unsigned, const TargetRegisterClass*>
    getRegForInlineAsmConstraint(const std::string &Constraint, EVT VT) const;
    std::vector<unsigned>
    getRegClassForInlineAsmConstraint(const std::string &Constraint,
                                      EVT VT) const;

    virtual bool isOffsetFoldingLegal(const GlobalAddressSDNode *GA) const;

    /// getFunctionAlignment - Return the Log2 alignment of this function.
    virtual unsigned getFunctionAlignment(const Function *F) const;

    virtual SDValue
      LowerFormalArguments(SDValue Chain,
                           CallingConv::ID CallConv,
                           bool isVarArg,
                           const SmallVectorImpl<ISD::InputArg> &Ins,
                           DebugLoc dl, SelectionDAG &DAG,
                           SmallVectorImpl<SDValue> &InVals) const;

    virtual SDValue
      LowerCall(SDValue Chain, SDValue Callee,
                CallingConv::ID CallConv, bool isVarArg,
                bool &isTailCall,
                const SmallVectorImpl<ISD::OutputArg> &Outs,
                const SmallVectorImpl<SDValue> &OutVals,
                const SmallVectorImpl<ISD::InputArg> &Ins,
                DebugLoc dl, SelectionDAG &DAG,
                SmallVectorImpl<SDValue> &InVals) const;

    virtual SDValue
      LowerReturn(SDValue Chain,
                  CallingConv::ID CallConv, bool isVarArg,
                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                  const SmallVectorImpl<SDValue> &OutVals,
                  DebugLoc dl, SelectionDAG &DAG) const;

    SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
    SDValue LowerConstantPool(SDValue Op, SelectionDAG &DAG) const;

    unsigned getSRetArgSize(SelectionDAG &DAG, SDValue Callee) const;
*/
  };
} // end namespace llvm

#endif    // MDSP_ISELLOWERING_H
