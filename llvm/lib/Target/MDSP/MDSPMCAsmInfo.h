//=====-- MDSPMCAsmInfo.h - MDSP asm properties -------------*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the MDSPMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPTARGETASMINFO_H
#define MDSPTARGETASMINFO_H

#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class Target;

  struct MDSPMCAsmInfo : public MCAsmInfo {
    explicit MDSPMCAsmInfo(const Target &T, StringRef TT);
  };

} // namespace llvm



#endif
