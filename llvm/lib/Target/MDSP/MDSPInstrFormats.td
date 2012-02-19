//===- MDSPInstrFormats.td - MDSP Instruction Formats ----*- tablegen -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//

class InstMDSP<dag outs, dag ins, string asmstr, list<dag> pattern> : Instuction {
  field bits<32> Inst;

  let Namespace = "MDSP";
  
  bits<3> type;
  let Inst{31-29} = type;
  
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
}

class MOVE<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   bits<3> op, am; //operation code, addressing mode
   bits<2> sd; //multi-purpose, source/dest
   let type = 0;
}

class ALU<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   let type = 1;
}

class MAC<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   let type = 2;
}

class DMAC<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   let type = 3;
}

class SIMD<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   let type = 4;
}

class P_FLOW<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   let type = 5;
}

/* types 6 and 7 are reserved for future use, according to ISA */
