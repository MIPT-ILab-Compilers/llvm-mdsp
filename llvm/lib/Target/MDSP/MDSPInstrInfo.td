//===- MDSPInstrInfo.td - Target Description for MDSP Target --------------===//
// 
//                     The LLVM Compiler Infrastructure
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

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;
def ADDRri : ComplexPattern<i32, 2, "SelectADDRri", [frameindex], []>;

// Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, GPR);
}
def MEMri : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, i32imm);
}
/// ===========================================

def LDrr   : F3_1<3, 0b000000,
                  (outs GPR:$dst), (ins MEMrr:$addr),
                  "ld [$addr], $dst",
                  [(set GPR:$dst, (load ADDRrr:$addr))]>;
def LDri   : F3_2<3, 0b000000,
                  (outs GPR:$dst), (ins  MEMri:$addr),
                  "ld [$addr], $dst",
                  [(set GPR:$dst, (load ADDRri:$addr))]>;
/// ===========================================

def STrr   : F3_1<3, 0b000100,
                  (outs), (ins MEMrr:$addr, GPR:$src),
                  "st $src, [$addr]",
                  [(store GPR:$src, ADDRrr:$addr)]>;
def STri   : F3_2<3, 0b000100,
                  (outs), (ins MEMri:$addr, GPR:$src),
                  "st $src, [$addr]",
                  [(store GPR:$src, ADDRri:$addr)]>;
/// ===========================================
