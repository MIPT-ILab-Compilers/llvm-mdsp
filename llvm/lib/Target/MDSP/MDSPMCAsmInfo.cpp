//===-- MDSPMCAsmInfo.cpp - MDSP asm properties ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the MDSPMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "MDSPMCAsmInfo.h"

using namespace llvm;

MDSPMCAsmInfo::MDSPMCAsmInfo(const Target &T, StringRef TT) {
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = 0;
  ZeroDirective = "\t.skip\t";
  CommentString = "!";
  HasLEB128 = true;
  SupportsDebugInformation = true;
  
  SunStyleELFSectionSwitchSyntax = true;
  UsesELFSectionDirectiveForBSS = true;

  WeakRefDirective = "\t.weak\t";

  PrivateGlobalPrefix = ".L";
}


