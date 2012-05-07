//===- MDSPInstrFormats.td - MDSP Instruction Formats ----*- tablegen -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//

class InstMDSP<dag outs, dag ins, 
               string asmstr, list<dag> pattern> 
  : Instruction {
  field bits<32> Inst;

  let Namespace = "MDSP";
  
  bits<3> type;
  bits<3> am;
  let am = 0b000; //why bothering about other modes?
  let Inst{31-29} = type;
  
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
}

class MOVE<bits<3> op, bits<2> sd, dag outs, dag ins, 
           string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   //bits<3> op; //operation code
   //bits<2> sd; //multi-purpose, source/dest
   let type = 0;
   let Inst{28-26} = op;
   let Inst{25-23} = am;
   let Inst{22-21} = sd;
}

class ALU<bits<3> logic, bits<5> arith, bits<3> shift, dag outs, dag ins, 
          string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   //bits<3> logic;
   //bits<5> arith;
   //bits<3> shift;
   let type = 1;
   let Inst{28-26} = logic;
   let Inst{25-21} = arith;
   let Inst{20-18} = shift;
   let Inst{17-15} = am;
}

class MAC<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   bits<4> op;
   bits<2> d; //destination selection
   let type = 2;
   let Inst{28-25} = op;
   let Inst{24-22} = am;
   let Inst{21-20} = d;
}

class DMAC<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   bits<5> op;
   bits<1> pre_am;
   let type = 3;
   let Inst{28-24} = op;
   let Inst{23} = pre_am;
}

class SIMD<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   bits<5> op;
   bits<1> ip; //input precision
   bits<8> mao; //memory access order
   bits<1> d; //destination
   bits<3> sba; //source base address
   let type = 4;
   let Inst{28-24} = op;
   let Inst{23-21} = am;
   let Inst{20} = ip;
   let Inst{19-12} = mao;
   let Inst{11} = d;
   let Inst{5-3} = sba;
}

class P_FLOW<dag outs, dag ins, string asmstr, list<dag> pattern> 
   : InstMDSP <outs, ins, asmstr, pattern> {
   bits<4> op;
   bits<1> addr;
   bits<1> gpr;
   bits<7> nr_instr;
   let type = 5;
   let Inst{28-25} = op;
   let Inst{24} = addr;
   let Inst{23} = gpr;
   let Inst{22-16} = nr_instr;
}

/* types 6 and 7 are reserved for future use, according to ISA */
