//===- MDSPInstrInfo.td - Target Description for MDSP Target ------------===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
// This file describes the MDSP instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "MDSPInstrFormats.td"

let op = 0 in 
  def NOP : MOVE<(outs), (ins), "nop", []>;
