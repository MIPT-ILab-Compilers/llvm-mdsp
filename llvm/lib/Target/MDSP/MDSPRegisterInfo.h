//===- MDSPRegisterInfo.h - MDSP Register Information Impl ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPREGISTERINFO_H
#define MDSPREGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"
#include "MDSPGenRegisterInfo.h.inc"

namespace llvm {

class MDSPSubtarget;
class TargetInstrInfo;
class Type;

struct MDSPRegisterInfo : public MDSPGenRegisterInfo {
  MDSPSubtarget &Subtarget;
  const TargetInstrInfo &TII;

  MDSPRegisterInfo(MDSPSubtarget &st, const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  const unsigned *getCalleeSavedRegs(const MachineFunction *MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I) const;

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, RegScavenger *RS = NULL) const;

  void processFunctionBeforeFrameFinalized(MachineFunction &MF) const;

  // Debug information queries.
  unsigned getRARegister() const;
  unsigned getFrameRegister(const MachineFunction &MF) const;

  // Exception handling queries.
  unsigned getEHExceptionRegister() const;
  unsigned getEHHandlerRegister() const;

  int getDwarfRegNum(unsigned RegNum, bool isEH) const;
};

} // end namespace llvm

#endif
