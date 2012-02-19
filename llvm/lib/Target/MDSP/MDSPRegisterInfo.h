//===- MDSPRegisterInfo.h - MDSP Register Information Impl ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MSDPREGISTERINFO_H
#define MSDPREGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"
#include "MDSPGenRegisterInfo.h.inc"

namespace llvm {

class TargetInstrInfo;
class Type;

struct MDSPRegisterInfo : public MDSPGenRegisterInfo {
    const TargetInstrInfo &TII;

    MDSPRegisterInfo(const TargetInstrInfo &tii);
};

} // end namespace llvm

#endif
