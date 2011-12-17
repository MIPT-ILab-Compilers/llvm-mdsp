// MDSP

class InstMDSP<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction {
  field bits<32> Inst;

  let Namespace = "MDSP";

  bits<2> op;
  let Inst{31-30} = op;               // Top two bits are the 'op' field
  
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
}


// Specific F3 classes: SparcV8 manual, page 44
//

class F3<dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstMDSP<outs, ins, asmstr, pattern> {
  bits<5> rd;
  bits<6> op3;
  bits<5> rs1;
  let op{1} = 1;   // Op = 2 or 3
  let Inst{29-25} = rd;
  let Inst{24-19} = op3;
  let Inst{18-14} = rs1;
}

class F3_1<bits<2> opVal, bits<6> op3val, dag outs, dag ins,
           string asmstr, list<dag> pattern> : F3<outs, ins, asmstr, pattern> {
  bits<8> asi = 0; // asi not currently used
  bits<5> rs2;

  let op         = opVal;
  let op3        = op3val;

  let Inst{13}   = 0;     // i field = 0
  let Inst{12-5} = asi;   // address space identifier
  let Inst{4-0}  = rs2;
}

class F3_2<bits<2> opVal, bits<6> op3val, dag outs, dag ins, 
           string asmstr, list<dag> pattern> : F3<outs, ins, asmstr, pattern> {
  bits<13> simm13;

  let op         = opVal;
  let op3        = op3val;

  let Inst{13}   = 1;     // i field = 1
  let Inst{12-0} = simm13;
}

