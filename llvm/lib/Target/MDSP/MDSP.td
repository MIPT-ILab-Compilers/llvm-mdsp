//===- MDSP.td - Describe the Sparc Target Machine --------*- tablegen -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//

//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "MDSPRegisterInfo.td"
include "MDSPCallingConv.td"
include "MDSPInstrInfo.td"

def MDSPInstrInfo : InstrInfo;

//===---------------------------------------------------------------------===//
// Define target what we're implementing
//===---------------------------------------------------------------------===//

def MDSP : Target {
	let InstructionSet = MDSPInstrInfo;
}

