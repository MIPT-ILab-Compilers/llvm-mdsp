//===- MDSPInstrFormats.td - MDSP Instruction Formats ------*- tablegen -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//


class InstMDSP <dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction {
 	field bits<32> Inst;

 	let Namespace = "MDSP";

	bits <3> Type;
 	let Inst {31 - 29} = Type;      
  
	dag OutOperandList = outs;
	dag InOperandList  = ins;
	let AsmString      = asmstr;
	let Pattern 	   = pattern;
}

class MOVEInst <bits <3> op, bits <2> s_d, dag outs, dag ins, string asmstr, list<dag> pattern> 
	: InstMDSP <outs, ins, asmstr, pattern> {
	
	let Type = 0b000;

	bits <3> OP;
	bits <3> AM;
	bits <2> S_D;
	let Inst {28 - 26} = OP;
	let Inst {25 - 23} = AM;
	let Inst {22 - 21} = S_D;

	let OP = op;
	let AM = 0b000;			// temporary step, because of tough addressing model
}

class ALUInst  <bits <3> logic, bits <5> arithmetic, bits <3> shift, 
		dag outs, dag ins, string asmstr, list<dag> pattern> 
	: InstMDSP <outs, ins, asmstr, pattern> {
	
	let Type = 0b001;

	bits <3> Logic;
	bits <5> Arithmetic;
	bits <3> Shift;
	bits <3> AM;
	let Inst {28 - 26} = Logic;
	let Inst {25 - 21} = Arithmetic;
	let Inst {20 - 18} = Shift;
	let Inst {17 - 15} = AM;

	let AM = 0b000;			// temporary step, because of tough addressing model
}
