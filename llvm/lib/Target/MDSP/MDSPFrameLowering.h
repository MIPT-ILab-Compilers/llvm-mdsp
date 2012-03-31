//===- MDSPFrameLowering.h - Define frame lowering for MDSP --*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef MDSP_FRAMEINFO_H
#define MDSP_FRAMEINFO_H

#include "MDSP.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
  class MDSPSubtarget;

class MDSPFrameLowering : public TargetFrameLowering {
public:
  explicit MDSPFrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 8, 0) {
  }

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;

  bool hasFP(const MachineFunction &MF) const { return false; }
};

} // End llvm namespace

#endif
