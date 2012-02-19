//===- MDSPRegisterInfo.cpp - MDSP Register Information -------*- C++ -*-===//
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
  : MDSPGenRegisterInfo(MDSP::ADJCALLSTACKDOWN, MDSP::ADJCALLSTACKUP), TII(tii) {

}
