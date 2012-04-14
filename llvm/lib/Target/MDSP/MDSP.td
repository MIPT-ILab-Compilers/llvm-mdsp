//===- MDSP.td - Describe the MDSP Target Machine --------*- tablegen -*-===//
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

 
def FeatureV9
  : SubtargetFeature<"v9", "Is", "true",
                     "Enable SPARC-V9 instructions">;

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "MDSPRegisterInfo.td"
include "MDSPCallingConv.td"
include "MDSPInstrInfo.td"

def MDSPInstrInfo : InstrInfo;


class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;


def : Proc<"v9",              [FeatureV9]>;

//===---------------------------------------------------------------------===//
// Define target what we're implementing
//===---------------------------------------------------------------------===//

def MDSP : Target {
	let InstructionSet = MDSPInstrInfo;
}


