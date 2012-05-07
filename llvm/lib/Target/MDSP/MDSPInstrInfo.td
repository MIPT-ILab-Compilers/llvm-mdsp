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

//Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, GPR);
}
def MEMri : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, i16imm);
}

def NOP : MOVE<0b000, 0b00, (outs), (ins), "nop", []>;

//def BMM : MOVE<

//Destination is GPR
/*def LDri : MOVE<0b110, 0b00, 
                (outs GPR:$dst), (ins MEMri:$src), 
                "ld $src, $dst", 
                [(set GPR:$dst, (load i16:$src))]>; 
*/
            
//Destination is APR, imm is address 
/*
def LDai : MOVE<0b110, 0b01, 

                (outs GPR:$dst), (ins MEMrr:$addr),
                "ld $src, ($addr)",
                [(set GPR:$dst, (load i16:$addr))]>;
*/
//Destination is memory 
//def LDmi : MOVE<0b110, 0b10,
