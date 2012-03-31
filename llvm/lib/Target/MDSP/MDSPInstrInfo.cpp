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
//#include "MDSPMachineFunctionInfo.h"
using namespace llvm;

MDSPInstrInfo::MDSPInstrInfo() 
  : TargetInstrInfoImpl(MDSPInsts, array_lengthof(MDSPInsts)),
    RI(*this){
}
