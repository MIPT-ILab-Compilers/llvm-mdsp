//===- MDSPRegisterInfo.h - MDSP Register Information Impl ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MSDPREGISTERINFO_H
#define MSDPREGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"
#include "MDSPGenRegisterInfo.h.inc"

namespace llvm {

class TargetInstrInfo;
class Type;

struct MDSPRegisterInfo : public MDSPGenRegisterInfo {
  const TargetInstrInfo &TII;

  MDSPRegisterInfo(const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  const unsigned *getCalleeSavedRegs(const MachineFunction *MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I) const;

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, RegScavenger *RS = NULL) const;

  // Debug information queries.
  unsigned getRARegister() const;
  unsigned getFrameRegister(const MachineFunction &MF) const;

  int getDwarfRegNum(unsigned RegNum, bool isEH) const;
};

} // end namespace llvm

#endif
