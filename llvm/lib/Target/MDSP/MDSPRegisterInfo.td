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

include "llvm/Target/Target.td"

class MDSPReg<string n> : Register<n> {
  field bits<5> Num;
  let Namespace = "MDSP";
}

class MDSPGPRReg<bits<5> num, string n> : MDSPReg<n> {
  let Num = num;
}

// General purpose register set
def R0 : MDSPGPRReg< 0, "R0">, DwarfRegNum<[0]>;
def R1 : MDSPGPRReg< 1, "R1">, DwarfRegNum<[1]>;
def R2 : MDSPGPRReg< 2, "R2">, DwarfRegNum<[2]>;
def R3 : MDSPGPRReg< 3, "R3">, DwarfRegNum<[3]>;
def R4 : MDSPGPRReg< 4, "R4">, DwarfRegNum<[4]>;
def R5 : MDSPGPRReg< 5, "R5">, DwarfRegNum<[5]>;
def R6 : MDSPGPRReg< 6, "R6">, DwarfRegNum<[6]>;
def R7 : MDSPGPRReg< 7, "R7">, DwarfRegNum<[7]>;
def R8 : MDSPGPRReg< 8, "R8">, DwarfRegNum<[8]>;
def R9 : MDSPGPRReg< 9, "R9">, DwarfRegNum<[9]>;
def R10 : MDSPGPRReg< 10, "R10">, DwarfRegNum<[10]>;
def R11 : MDSPGPRReg< 11, "R11">, DwarfRegNum<[11]>;
def R12 : MDSPGPRReg< 12, "R12">, DwarfRegNum<[12]>;
def R13 : MDSPGPRReg< 13, "R13">, DwarfRegNum<[13]>;
def R14 : MDSPGPRReg< 14, "R14">, DwarfRegNum<[14]>;
def R15 : MDSPGPRReg< 15, "R15">, DwarfRegNum<[15]>;
def R16 : MDSPGPRReg< 16, "R16">, DwarfRegNum<[16]>;
def R17 : MDSPGPRReg< 17, "R17">, DwarfRegNum<[17]>;
def R18 : MDSPGPRReg< 18, "R18">, DwarfRegNum<[18]>;
def R19 : MDSPGPRReg< 19, "R19">, DwarfRegNum<[19]>;
def R20 : MDSPGPRReg< 20, "R20">, DwarfRegNum<[20]>;
def R21 : MDSPGPRReg< 21, "R21">, DwarfRegNum<[21]>;
def R22 : MDSPGPRReg< 22, "R22">, DwarfRegNum<[22]>;
def R23 : MDSPGPRReg< 23, "R23">, DwarfRegNum<[23]>;
def R24 : MDSPGPRReg< 24, "R24">, DwarfRegNum<[24]>;
def R25 : MDSPGPRReg< 25, "R25">, DwarfRegNum<[25]>;
def R26 : MDSPGPRReg< 26, "R26">, DwarfRegNum<[26]>;
def R27 : MDSPGPRReg< 27, "R27">, DwarfRegNum<[27]>;
def R28 : MDSPGPRReg< 28, "R28">, DwarfRegNum<[28]>;
def R29 : MDSPGPRReg< 29, "R29">, DwarfRegNum<[29]>;
def R30 : MDSPGPRReg< 30, "R30">, DwarfRegNum<[30]>;
def R31 : MDSPGPRReg< 31, "R31">, DwarfRegNum<[31]>;

def GPRRegs : RegisterClass<"MDSP", [i16], 16, [R0, R1, R2, R3, R4, R5, 
                                    R6, R7, R7, R8, R9, R10, R11, 
                                    R12, R13, R14, R15, R16, R17, 
                                    R18, R19, R20, R21, R22, R23, 
                                    R24, R25, R26, R27, R28, R29,
                                    R30, R31]>;
