//===-- MDSPTargetMachine.h - Define TargetMachine for MDSP ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the MDSP specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPTARGETMACHINE_H
#define MDSPTARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm
{

class MDSPTargetMachine : public LLVMTargetMachine
{
  const TargetData DataLayout;       // Calculates type size & alignment

public:
  MDSPTargetMachine (const Target &T, const std::string &TT, const std::string &FS);

  virtual const TargetData       *getTargetData() const { return &DataLayout; }
};

} // end namespace llvm

#endif
