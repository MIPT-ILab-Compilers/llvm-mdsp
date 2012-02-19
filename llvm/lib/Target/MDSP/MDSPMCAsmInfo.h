//=====-- MDSPMCAsmInfo.h - MDSP asm properties -------------*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
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

  struct MDSPELFMCAsmInfo : public MCAsmInfo {
    explicit MDSPELFMCAsmInfo(const Target &T, StringRef TT);
  };

} // namespace llvm

#endif
