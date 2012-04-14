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

#ifndef MDSPFRAMEINFO_H
#define MDSPFRAMEINFO_H

#include "MDSP.h"
#include "MDSPSubtarget.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
class MDSPSubtarget;

class MDSPFrameLowering : public TargetFrameLowering {
	  const MDSPSubtarget &STI;
public:
  explicit MDSPFrameLowering(const MDSPSubtarget &sti)
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 8, 0),  STI(sti) {
  }

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;

  bool hasFP(const MachineFunction &MF) const { return false; }
};

} // End llvm namespace

#endif
