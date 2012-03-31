//===- MDSPRegisterInfo.td - MDSP Register defs --------------*- tablegen -*-===//
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
  let Namespace = "MDSP";
}

class GPR<bits<5> num, string n> : MDSPReg<n> {
  field bits<5> Num = num;
}

// General purpose register set
def R0 : GPR< 0, "R0">, DwarfRegNum<[0]>;
def R1 : GPR< 1, "R1">, DwarfRegNum<[1]>;
/*def R2 : RegGPR< 2, "R2">, DwarfRegNum<[2]>;
def R3 : RegGPR< 3, "R3">, DwarfRegNum<[3]>;
def R4 : RegGPR< 4, "R4">, DwarfRegNum<[4]>;
def R5 : RegGPR< 5, "R5">, DwarfRegNum<[5]>;
def R6 : RegGPR< 6, "R6">, DwarfRegNum<[6]>;
def R7 : RegGPR< 7, "R7">, DwarfRegNum<[7]>;
def R8 : RegGPR< 8, "R8">, DwarfRegNum<[8]>;
def R9 : RegGPR< 9, "R9">, DwarfRegNum<[9]>;
def R10 : RegGPR< 10, "R10">, DwarfRegNum<[10]>;
def R11 : RegGPR< 11, "R11">, DwarfRegNum<[11]>;
def R12 : RegGPR< 12, "R12">, DwarfRegNum<[12]>;
def R13 : RegGPR< 13, "R13">, DwarfRegNum<[13]>;
def R14 : RegGPR< 14, "R14">, DwarfRegNum<[14]>;
def R15 : RegGPR< 15, "R15">, DwarfRegNum<[15]>;
def R16 : RegGPR< 16, "R16">, DwarfRegNum<[16]>;
def R17 : GPR< 17, "R17">, DwarfRegNum<[17]>;
def R18 : GPR< 18, "R18">, DwarfRegNum<[18]>;
def R19 : GPR< 19, "R19">, DwarfRegNum<[19]>;
def R20 : GPR< 20, "R20">, DwarfRegNum<[20]>;
def R21 : GPR< 21, "R21">, DwarfRegNum<[21]>;
def R22 : GPR< 22, "R22">, DwarfRegNum<[22]>;
def R23 : GPR< 23, "R23">, DwarfRegNum<[23]>;
def R24 : GPR< 24, "R24">, DwarfRegNum<[24]>;
def R25 : GPR< 25, "R25">, DwarfRegNum<[25]>;
def R26 : GPR< 26, "R26">, DwarfRegNum<[26]>;
def R27 : GPR< 27, "R27">, DwarfRegNum<[27]>;
def R28 : GPR< 28, "R28">, DwarfRegNum<[28]>;
def R29 : GPR< 29, "R29">, DwarfRegNum<[29]>;
def R30 : GPR< 30, "R30">, DwarfRegNum<[30]>;
def R31 : RegGPR< 31, "R31">, DwarfRegNum<[31]>;
*/

/*def GPR : RegisterClass<"MDSP", [i16], 16, 
     [R0, R1, R2, R3, R4, R5, R6, R7, R7, R8, R9, R10, R11, R12, R13, R14, R15, 
     R16, R17, R18, R19, R20, R21, R22, R23, R24, R25, R26, R27, R28, R29, R30, 
     R31]>;
*/
def GPR : RegisterClass<"MDSP", [i16], 16, [R0, R1]>;
