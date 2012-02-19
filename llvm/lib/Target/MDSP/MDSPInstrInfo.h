//===- MDSPInstrInfo.h - MDSP Instruction Information ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
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
   
   virtual const MDSPRegisterInfo &getRegisterInfo() const { return RI; }

}

}

#endif
