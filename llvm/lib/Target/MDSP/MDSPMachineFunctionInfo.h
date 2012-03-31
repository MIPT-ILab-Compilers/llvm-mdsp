//===- MDSPMachineFunctionInfo.h - MDSP Machine Function Info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares  MDSP specific per-machine-function information.
//
//===----------------------------------------------------------------------===//
#ifndef MDSPMACHINEFUNCTIONINFO_H
#define MDSPMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

  class MDSPMachineFunctionInfo : public MachineFunctionInfo {
  private:
    unsigned GlobalBaseReg;

    /// VarArgsFrameOffset - Frame offset to start of varargs area.
    int VarArgsFrameOffset;

    /// SRetReturnReg - Holds the virtual register into which the sret
    /// argument is passed.
    unsigned SRetReturnReg;
  public:
    MDSPMachineFunctionInfo()
      : GlobalBaseReg(0), VarArgsFrameOffset(0), SRetReturnReg(0) {}
    explicit MDSPMachineFunctionInfo(MachineFunction &MF)
      : GlobalBaseReg(0), VarArgsFrameOffset(0), SRetReturnReg(0) {}

    unsigned getGlobalBaseReg() const { return GlobalBaseReg; }
    void setGlobalBaseReg(unsigned Reg) { GlobalBaseReg = Reg; }

    int getVarArgsFrameOffset() const { return VarArgsFrameOffset; }
    void setVarArgsFrameOffset(int Offset) { VarArgsFrameOffset = Offset; }

    unsigned getSRetReturnReg() const { return SRetReturnReg; }
    void setSRetReturnReg(unsigned Reg) { SRetReturnReg = Reg; }
  };
}

#endif
