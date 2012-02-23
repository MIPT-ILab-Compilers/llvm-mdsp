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

/*
// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;
def ADDRri : ComplexPattern<i32, 2, "SelectADDRri", [frameindex], []>;
*/
// Address operands
def MEMrr : Operand<i16> {
	let PrintMethod = "printMemOperand";
	let MIOperandInfo = (ops APR, APR);
}
def MEMri : Operand<i16> {
	let PrintMethod = "printMemOperand";
	let MIOperandInfo = (ops APR, i16imm);
}

def MEMra  : Operand<i16> {				
	let PrintMethod = "printMemOperand";
	let MIOperandInfo = (ops APR);
}

/// ===========================================


/// Ld instructions, p. 182

/// ld 0, i16imm, rD  ; 	imm16 -> rD
///
def LDir : MOVEInst <0b110, 0b00, (outs GPR:$dst), (ins i16imm:$src),
		 "ld 0, $src, $dst", []> {
}

/// ld 0, i16imm, aprD  ;  	imm16 -> aprD,
///
def LDia : MOVEInst <0b110, 0b01, (outs APR:$dst), (ins i16imm:$src),
		 "ld 1, $src, $dst", []> {
}


/// B instructions, p. 147

/// br rS, rD  ;	rS -> rD
///
def BRR :  MOVEInst <0b011, 0b00, (outs GPR:$dst), (ins GPR:$src),
		 "brr $src, $dst", []> {
}

/// ALU instructions

/// add rS1, rS2, rD
///
def ADDrr : ALUInst <0, 0b00001, 0, (outs GPR:$dst), (ins GPR:$src1, GPR:$src2),
		 "add $src1, $src2, $dst", []> {
}

/// ===========================================
