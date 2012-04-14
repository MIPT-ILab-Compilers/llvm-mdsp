//====- MDSPFrameLowering.cpp - MDSP Frame Information ---------*- C++ -*-====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "MDSPFrameLowering.h"
#include "MDSPInstrInfo.h"
#include "MDSPMachineFunctionInfo.h"
#include "llvm/Function.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

void MDSPFrameLowering::emitPrologue(MachineFunction &MF) const {}

void MDSPFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {}
