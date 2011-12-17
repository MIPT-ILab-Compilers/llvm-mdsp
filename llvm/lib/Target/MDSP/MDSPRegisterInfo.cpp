//===- MDSPRegisterInfo.cpp - MDSP Register Information -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "MDSP.h"
#include "MDSPRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineLocation.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/Type.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"

using namespace llvm;

MDSPRegisterInfo::MDSPRegisterInfo(const TargetInstrInfo &tii)
             : MDSPGenRegisterInfo(-1, -1), TII(tii) {}

const unsigned* MDSPRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const unsigned CalleeSavedRegs[] = { 0 };
  return CalleeSavedRegs;
}

BitVector MDSPRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(0);
  return Reserved;
}

void MDSPRegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {}

void
MDSPRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                      int SPAdj, RegScavenger *RS) const {
}

void MDSPRegisterInfo::
processFunctionBeforeFrameFinalized(MachineFunction &MF) const {}

unsigned MDSPRegisterInfo::getRARegister() const {
  return 0;
}

unsigned MDSPRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return 0;
}

unsigned MDSPRegisterInfo::getEHExceptionRegister() const {
  llvm_unreachable("What is the exception register");
  return 0;
}

unsigned MDSPRegisterInfo::getEHHandlerRegister() const {
  llvm_unreachable("What is the exception handler register");
  return 0;
}

int MDSPRegisterInfo::getDwarfRegNum(unsigned RegNum, bool isEH) const {
  return MDSPGenRegisterInfo::getDwarfRegNumFull(RegNum, 0);
}

#include "MDSPGenRegisterInfo.inc"
