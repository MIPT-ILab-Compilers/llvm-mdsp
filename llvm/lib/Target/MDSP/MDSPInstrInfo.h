//===- MDSPInstrInfo.h - MDSP Instruction Information -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPINSTRUCTIONINFO_H
#define MDSPINSTRUCTIONINFO_H

#include "llvm/Target/TargetInstrInfo.h"
#include "MDSPRegisterInfo.h"

namespace llvm {

class MDSPInstrInfo : public TargetInstrInfoImpl {
  const MDSPRegisterInfo RI;
public:
  explicit MDSPInstrInfo(void);
};

}

#endif
