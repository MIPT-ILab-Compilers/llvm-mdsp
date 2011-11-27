//===- TableGen'erated file -------------------------------------*- C++ -*-===//
//
// Register Information Source Fragment
//
// Automatically generated file, do not edit!
//
//===----------------------------------------------------------------------===//

namespace llvm {

namespace {     // Register classes...
  // GPR Register Class...
  static const unsigned GPR[] = {
    MDSP::GPR0, MDSP::GPR1, MDSP::GPR2, MDSP::GPR3, MDSP::GPR4, MDSP::GPR5, MDSP::GPR6, MDSP::GPR7, MDSP::GPR8, MDSP::GPR9, MDSP::GPR10, MDSP::GPR11, MDSP::GPR12, MDSP::GPR13, MDSP::GPR14, MDSP::GPR15, MDSP::GPR16, MDSP::GPR17, MDSP::GPR18, MDSP::GPR19, MDSP::GPR20, MDSP::GPR21, MDSP::GPR22, MDSP::GPR23, MDSP::GPR24, MDSP::GPR25, MDSP::GPR26, MDSP::GPR27, MDSP::GPR28, MDSP::GPR29, MDSP::GPR30, MDSP::GPR31, 
  };

  // GPRVTs Register Class Value Types...
  static const EVT GPRVTs[] = {
    MVT::i16, MVT::Other
  };

}  // end anonymous namespace

namespace GPR {   // Register class instances
  GPRClass	GPRRegClass;

  static const TargetRegisterClass* const NullRegClasses[] = { NULL };

  // GPR Register Class sub-classes...
  static const TargetRegisterClass* const GPRSubclasses[] = {
    NULL
  };

  // GPR Register Class super-classes...
  static const TargetRegisterClass* const GPRSuperclasses[] = {
    NULL
  };


GPRClass::GPRClass()  : TargetRegisterClass(GPRRegClassID, "GPR", GPRVTs, GPRSubclasses, GPRSuperclasses, NullRegClasses, NullRegClasses, 2, 4, 1, GPR, GPR + 32) {}
}

namespace {
  const TargetRegisterClass* const RegisterClasses[] = {
    &GPR::GPRRegClass,
  };


  // Number of hash collisions: 0
  const unsigned SubregHashTable[] = { MDSP::NoRegister, MDSP::NoRegister, 
MDSP::NoRegister, MDSP::NoRegister };
  const unsigned SubregHashTableSize = 2;


  // Number of hash collisions: 0
  const unsigned AliasesHashTable[] = { MDSP::NoRegister, MDSP::NoRegister, 
MDSP::NoRegister, MDSP::NoRegister };
  const unsigned AliasesHashTableSize = 2;


  // Register Overlap Lists...
  const unsigned GPR0_Overlaps[] = { MDSP::GPR0, 0 };
  const unsigned GPR1_Overlaps[] = { MDSP::GPR1, 0 };
  const unsigned GPR2_Overlaps[] = { MDSP::GPR2, 0 };
  const unsigned GPR3_Overlaps[] = { MDSP::GPR3, 0 };
  const unsigned GPR4_Overlaps[] = { MDSP::GPR4, 0 };
  const unsigned GPR5_Overlaps[] = { MDSP::GPR5, 0 };
  const unsigned GPR6_Overlaps[] = { MDSP::GPR6, 0 };
  const unsigned GPR7_Overlaps[] = { MDSP::GPR7, 0 };
  const unsigned GPR8_Overlaps[] = { MDSP::GPR8, 0 };
  const unsigned GPR9_Overlaps[] = { MDSP::GPR9, 0 };
  const unsigned GPR10_Overlaps[] = { MDSP::GPR10, 0 };
  const unsigned GPR11_Overlaps[] = { MDSP::GPR11, 0 };
  const unsigned GPR12_Overlaps[] = { MDSP::GPR12, 0 };
  const unsigned GPR13_Overlaps[] = { MDSP::GPR13, 0 };
  const unsigned GPR14_Overlaps[] = { MDSP::GPR14, 0 };
  const unsigned GPR15_Overlaps[] = { MDSP::GPR15, 0 };
  const unsigned GPR16_Overlaps[] = { MDSP::GPR16, 0 };
  const unsigned GPR17_Overlaps[] = { MDSP::GPR17, 0 };
  const unsigned GPR18_Overlaps[] = { MDSP::GPR18, 0 };
  const unsigned GPR19_Overlaps[] = { MDSP::GPR19, 0 };
  const unsigned GPR20_Overlaps[] = { MDSP::GPR20, 0 };
  const unsigned GPR21_Overlaps[] = { MDSP::GPR21, 0 };
  const unsigned GPR22_Overlaps[] = { MDSP::GPR22, 0 };
  const unsigned GPR23_Overlaps[] = { MDSP::GPR23, 0 };
  const unsigned GPR24_Overlaps[] = { MDSP::GPR24, 0 };
  const unsigned GPR25_Overlaps[] = { MDSP::GPR25, 0 };
  const unsigned GPR26_Overlaps[] = { MDSP::GPR26, 0 };
  const unsigned GPR27_Overlaps[] = { MDSP::GPR27, 0 };
  const unsigned GPR28_Overlaps[] = { MDSP::GPR28, 0 };
  const unsigned GPR29_Overlaps[] = { MDSP::GPR29, 0 };
  const unsigned GPR30_Overlaps[] = { MDSP::GPR30, 0 };
  const unsigned GPR31_Overlaps[] = { MDSP::GPR31, 0 };


  // Register Sub-registers Sets...
  const unsigned Empty_SubRegsSet[] = { 0 };
  const unsigned Empty_SuperRegsSet[] = { 0 };

  const TargetRegisterDesc RegisterDescriptors[] = { // Descriptors
    { "NOREG",	0,	0,	0 },
    { "GPR0",	GPR0_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR1",	GPR1_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR2",	GPR2_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR3",	GPR3_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR4",	GPR4_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR5",	GPR5_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR6",	GPR6_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR7",	GPR7_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR8",	GPR8_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR9",	GPR9_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR10",	GPR10_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR11",	GPR11_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR12",	GPR12_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR13",	GPR13_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR14",	GPR14_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR15",	GPR15_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR16",	GPR16_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR17",	GPR17_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR18",	GPR18_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR19",	GPR19_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR20",	GPR20_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR21",	GPR21_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR22",	GPR22_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR23",	GPR23_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR24",	GPR24_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR25",	GPR25_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR26",	GPR26_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR27",	GPR27_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR28",	GPR28_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR29",	GPR29_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR30",	GPR30_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
    { "GPR31",	GPR31_Overlaps,	Empty_SubRegsSet,	Empty_SuperRegsSet },
  };

  const char *const SubRegIndexTable[] = { "" };

}

unsigned MDSPGenRegisterInfo::getSubReg(unsigned RegNo, unsigned Index) const {
  switch (RegNo) {
  default:
    return 0;
  };
  return 0;
}

unsigned MDSPGenRegisterInfo::getSubRegIndex(unsigned RegNo, unsigned SubRegNo) const {
  switch (RegNo) {
  default:
    return 0;
  };
  return 0;
}

unsigned MDSPGenRegisterInfo::composeSubRegIndices(unsigned IdxA, unsigned IdxB) const {
  switch (IdxA) {
  default:
    return IdxB;
  }
}

MDSPGenRegisterInfo::MDSPGenRegisterInfo(int CallFrameSetupOpcode, int CallFrameDestroyOpcode)
  : TargetRegisterInfo(RegisterDescriptors, 33, RegisterClasses, RegisterClasses+1,
                 SubRegIndexTable,
                 CallFrameSetupOpcode, CallFrameDestroyOpcode,
                 SubregHashTable, SubregHashTableSize,
                 AliasesHashTable, AliasesHashTableSize) {
}

int MDSPGenRegisterInfo::getDwarfRegNumFull(unsigned RegNum, unsigned Flavour) const {
  switch (Flavour) {
  default:
    assert(0 && "Unknown DWARF flavour");
    return -1;
  case 0:
    switch (RegNum) {
    default:
      assert(0 && "Invalid RegNum");
      return -1;
    case MDSP::GPR0:
      return 0;
    case MDSP::GPR1:
      return 1;
    case MDSP::GPR2:
      return 2;
    case MDSP::GPR3:
      return 3;
    case MDSP::GPR4:
      return 4;
    case MDSP::GPR5:
      return 5;
    case MDSP::GPR6:
      return 6;
    case MDSP::GPR7:
      return 7;
    case MDSP::GPR8:
      return 8;
    case MDSP::GPR9:
      return 9;
    case MDSP::GPR10:
      return 10;
    case MDSP::GPR11:
      return 11;
    case MDSP::GPR12:
      return 12;
    case MDSP::GPR13:
      return 13;
    case MDSP::GPR14:
      return 14;
    case MDSP::GPR15:
      return 15;
    case MDSP::GPR16:
      return 16;
    case MDSP::GPR17:
      return 17;
    case MDSP::GPR18:
      return 18;
    case MDSP::GPR19:
      return 19;
    case MDSP::GPR20:
      return 20;
    case MDSP::GPR21:
      return 21;
    case MDSP::GPR22:
      return 22;
    case MDSP::GPR23:
      return 23;
    case MDSP::GPR24:
      return 24;
    case MDSP::GPR25:
      return 25;
    case MDSP::GPR26:
      return 26;
    case MDSP::GPR27:
      return 27;
    case MDSP::GPR28:
      return 28;
    case MDSP::GPR29:
      return 29;
    case MDSP::GPR30:
      return 30;
    case MDSP::GPR31:
      return 31;
    };
  };
}

} // End llvm namespace 
