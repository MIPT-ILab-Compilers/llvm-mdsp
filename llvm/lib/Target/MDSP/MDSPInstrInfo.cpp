//===- MDSPInstrInfo.cpp - MDSP Instruction Information -------*- C++ -*-===//
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

#include "MDSPInstrInfo.h"
#include "MDSP.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "MDSPGenInstrInfo.inc"
#include "MDSPMachineFunctionInfo.h"
using namespace llvm;

MDSPInstrInfo::MDSPInstrInfo() 
  : TargetInstrInfoImpl(MDSPInsts, array_lengthof(MDSPInsts)),
    RI(*this){
}
/* 
unsigned MDSPInstrInfo::getGlobalBaseReg(MachineFunction *MF) const
{
  MDSPMachineFunctionInfo *MDSPFI = MF->getInfo<MDSPMachineFunctionInfo>();
  unsigned GlobalBaseReg = MDSPFI->getGlobalBaseReg();
  if (GlobalBaseReg != 0)
    return GlobalBaseReg;

  // Insert the set of GlobalBaseReg into the first MBB of the function
  MachineBasicBlock &FirstMBB = MF->front();
  MachineBasicBlock::iterator MBBI = FirstMBB.begin();
  MachineRegisterInfo &RegInfo = MF->getRegInfo();

  GlobalBaseReg = RegInfo.createVirtualRegister(&MDSP::GPRRegClass);


  DebugLoc dl;

  BuildMI(FirstMBB, MBBI, dl, get(MDSP::GETPCX), GlobalBaseReg);
  MDSPFI->setGlobalBaseReg(GlobalBaseReg);
  return GlobalBaseReg;
}
*/
