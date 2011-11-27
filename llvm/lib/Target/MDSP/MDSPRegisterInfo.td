//===- MDSPRegisterInfo.td - MDSP Register defs ----------*- tablegen -*-===//
// 
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the MDSP register file 
//===----------------------------------------------------------------------===//

class MDSPReg<string n> : Register<n> {
	field bits<5> Num;
	let Namespace  = "MDSP";
}

class RegGPR<bits<5> num, string n> : MDSPReg<n> {
	let Num = num;
}

//===----------------------------------------------------------------------===//
//  Declarations that describe General Purpose Registers
//===----------------------------------------------------------------------===//

def GPR0  : RegGPR< 0, "GPR0" >,  DwarfRegNum<[ 0]>;
def GPR1  : RegGPR< 1, "GPR1" >,  DwarfRegNum<[ 1]>;
def GPR2  : RegGPR< 2, "GPR2" >,  DwarfRegNum<[ 2]>;
def GPR3  : RegGPR< 3, "GPR3" >,  DwarfRegNum<[ 3]>;
def GPR4  : RegGPR< 4, "GPR4" >,  DwarfRegNum<[ 4]>;
def GPR5  : RegGPR< 5, "GPR5" >,  DwarfRegNum<[ 5]>;
def GPR6  : RegGPR< 6, "GPR6" >,  DwarfRegNum<[ 6]>;
def GPR7  : RegGPR< 7, "GPR7" >,  DwarfRegNum<[ 7]>;
def GPR8  : RegGPR< 8, "GPR8" >,  DwarfRegNum<[ 8]>;
def GPR9  : RegGPR< 9, "GPR9" >,  DwarfRegNum<[ 9]>;
def GPR10 : RegGPR<10, "GPR10">,  DwarfRegNum<[10]>;
def GPR11 : RegGPR<11, "GPR11">,  DwarfRegNum<[11]>;
def GPR12 : RegGPR<12, "GPR12">,  DwarfRegNum<[12]>;
def GPR13 : RegGPR<13, "GPR13">,  DwarfRegNum<[13]>;
def GPR14 : RegGPR<14, "GPR14">,  DwarfRegNum<[14]>;
def GPR15 : RegGPR<15, "GPR15">,  DwarfRegNum<[15]>;
def GPR16 : RegGPR<16, "GPR16">,  DwarfRegNum<[16]>;
def GPR17 : RegGPR<17, "GPR17">,  DwarfRegNum<[17]>;
def GPR18 : RegGPR<18, "GPR18">,  DwarfRegNum<[18]>;
def GPR19 : RegGPR<19, "GPR19">,  DwarfRegNum<[19]>;
def GPR20 : RegGPR<20, "GPR20">,  DwarfRegNum<[20]>;
def GPR21 : RegGPR<21, "GPR21">,  DwarfRegNum<[21]>;
def GPR22 : RegGPR<22, "GPR22">,  DwarfRegNum<[22]>;
def GPR23 : RegGPR<23, "GPR23">,  DwarfRegNum<[23]>;
def GPR24 : RegGPR<24, "GPR24">,  DwarfRegNum<[24]>;
def GPR25 : RegGPR<25, "GPR25">,  DwarfRegNum<[25]>;
def GPR26 : RegGPR<26, "GPR26">,  DwarfRegNum<[26]>;
def GPR27 : RegGPR<27, "GPR27">,  DwarfRegNum<[27]>;
def GPR28 : RegGPR<28, "GPR28">,  DwarfRegNum<[28]>;
def GPR29 : RegGPR<29, "GPR29">,  DwarfRegNum<[29]>;
def GPR30 : RegGPR<30, "GPR30">,  DwarfRegNum<[30]>;
def GPR31 : RegGPR<31, "GPR31">,  DwarfRegNum<[31]>;

def GPR : RegisterClass<"GPR", [i16], 32, [
			GPR0,  GPR1,  GPR2,  GPR3,  GPR4,  GPR5,  GPR6,  GPR7,
			GPR8,  GPR9,  GPR10, GPR11, GPR12, GPR13, GPR14, GPR15,
			GPR16, GPR17, GPR18, GPR19, GPR20, GPR21, GPR22, GPR23,
			GPR24, GPR25, GPR26, GPR27, GPR28, GPR29, GPR30, GPR31
			]> {
}


