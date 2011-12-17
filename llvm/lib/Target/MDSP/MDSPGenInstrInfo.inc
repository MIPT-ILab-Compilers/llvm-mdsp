//===- TableGen'erated file -------------------------------------*- C++ -*-===//
//
// Target Instruction Descriptors
//
// Automatically generated file, do not edit!
//
//===----------------------------------------------------------------------===//

namespace llvm {


static const TargetOperandInfo OperandInfo2[] = { { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo3[] = { { -1, 0, 0 }, { -1, 0, 0 }, { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo4[] = { { -1, 0, 0 }, { -1, 0, ((0 << 16) | (1 << TOI::TIED_TO)) }, { -1, 0, 0 }, { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo5[] = { { -1, 0, 0 }, { -1, 0, 0 }, { -1, 0, 0 }, { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo6[] = { { -1, 0, 0 }, { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo7[] = { { GPR::GPRRegClassID, 0, 0 }, { GPR::GPRRegClassID, 0, 0 }, { -1, 0, 0 }, };
static const TargetOperandInfo OperandInfo8[] = { { GPR::GPRRegClassID, 0, 0 }, { GPR::GPRRegClassID, 0, 0 }, { GPR::GPRRegClassID, 0, 0 }, };
static const TargetOperandInfo OperandInfo9[] = { { GPR::GPRRegClassID, 0, 0 }, { -1, 0, 0 }, { GPR::GPRRegClassID, 0, 0 }, };

static const TargetInstrDesc MDSPInsts[] = {
  { 0,	0,	0,	0,	"PHI", 0|(1<<TID::Variadic)|(1<<TID::UnmodeledSideEffects), 0x0ULL, NULL, NULL, NULL, 0 },  // Inst #0 = PHI
  { 1,	0,	0,	0,	"INLINEASM", 0|(1<<TID::Variadic), 0x0ULL, NULL, NULL, NULL, 0 },  // Inst #1 = INLINEASM
  { 2,	1,	0,	0,	"PROLOG_LABEL", 0|(1<<TID::NotDuplicable)|(1<<TID::UnmodeledSideEffects), 0x0ULL, NULL, NULL, NULL, OperandInfo2 },  // Inst #2 = PROLOG_LABEL
  { 3,	1,	0,	0,	"EH_LABEL", 0|(1<<TID::NotDuplicable)|(1<<TID::UnmodeledSideEffects), 0x0ULL, NULL, NULL, NULL, OperandInfo2 },  // Inst #3 = EH_LABEL
  { 4,	1,	0,	0,	"GC_LABEL", 0|(1<<TID::NotDuplicable)|(1<<TID::UnmodeledSideEffects), 0x0ULL, NULL, NULL, NULL, OperandInfo2 },  // Inst #4 = GC_LABEL
  { 5,	0,	0,	0,	"KILL", 0|(1<<TID::Variadic), 0x0ULL, NULL, NULL, NULL, 0 },  // Inst #5 = KILL
  { 6,	3,	1,	0,	"EXTRACT_SUBREG", 0, 0x0ULL, NULL, NULL, NULL, OperandInfo3 },  // Inst #6 = EXTRACT_SUBREG
  { 7,	4,	1,	0,	"INSERT_SUBREG", 0, 0x0ULL, NULL, NULL, NULL, OperandInfo4 },  // Inst #7 = INSERT_SUBREG
  { 8,	1,	1,	0,	"IMPLICIT_DEF", 0|(1<<TID::Rematerializable)|(1<<TID::CheapAsAMove), 0x0ULL, NULL, NULL, NULL, OperandInfo2 },  // Inst #8 = IMPLICIT_DEF
  { 9,	4,	1,	0,	"SUBREG_TO_REG", 0, 0x0ULL, NULL, NULL, NULL, OperandInfo5 },  // Inst #9 = SUBREG_TO_REG
  { 10,	3,	1,	0,	"COPY_TO_REGCLASS", 0|(1<<TID::CheapAsAMove), 0x0ULL, NULL, NULL, NULL, OperandInfo3 },  // Inst #10 = COPY_TO_REGCLASS
  { 11,	0,	0,	0,	"DBG_VALUE", 0|(1<<TID::Variadic), 0x0ULL, NULL, NULL, NULL, 0 },  // Inst #11 = DBG_VALUE
  { 12,	1,	1,	0,	"REG_SEQUENCE", 0|(1<<TID::Variadic)|(1<<TID::CheapAsAMove), 0x0ULL, NULL, NULL, NULL, OperandInfo2 },  // Inst #12 = REG_SEQUENCE
  { 13,	2,	1,	0,	"COPY", 0|(1<<TID::CheapAsAMove), 0x0ULL, NULL, NULL, NULL, OperandInfo6 },  // Inst #13 = COPY
  { 14,	3,	1,	0,	"LDri", 0|(1<<TID::MayLoad), 0x0ULL, NULL, NULL, NULL, OperandInfo7 },  // Inst #14 = LDri
  { 15,	3,	1,	0,	"LDrr", 0|(1<<TID::MayLoad), 0x0ULL, NULL, NULL, NULL, OperandInfo8 },  // Inst #15 = LDrr
  { 16,	3,	0,	0,	"STri", 0|(1<<TID::MayStore), 0x0ULL, NULL, NULL, NULL, OperandInfo9 },  // Inst #16 = STri
  { 17,	3,	0,	0,	"STrr", 0|(1<<TID::MayStore), 0x0ULL, NULL, NULL, NULL, OperandInfo8 },  // Inst #17 = STrr
};
} // End llvm namespace 
