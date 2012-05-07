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
  explicit MDSPInstrInfo(void); 

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  virtual const MDSPRegisterInfo &getRegisterInfo() const { return RI; }

  unsigned getGlobalBaseReg(MachineFunction *MF) const;
};

}

#endif
