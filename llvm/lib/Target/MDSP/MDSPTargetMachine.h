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

#include "MDSPInstrInfo.h"
#include "MDSPISelLowering.h"
#include "MDSPFrameLowering.h"
#include "MDSPSelectionDAGInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm
{

class MDSPTargetMachine : public LLVMTargetMachine
{
  const TargetData 		DataLayout;       // Calculates type size & alignment
  MDSPTargetLowering 	TLInfo;
  MDSPFrameLowering 	FrameLowering;
  MDSPSelectionDAGInfo 	TSInfo;

public:
  MDSPTargetMachine (const Target &T, const std::string &TT, const std::string &FS);

  virtual const TargetData       	*getTargetData() 	 const { return &DataLayout; }
  virtual const MDSPTargetLowering 	*getTargetLowering() const { return &TLInfo; }
  virtual const TargetFrameLowering *getFrameLowering()  const { return &FrameLowering; }

  // Pass Pipeline Configuration
  virtual bool addInstSelector(PassManagerBase &PM, CodeGenOpt::Level OptLevel);
//  virtual bool addPreEmitPass(PassManagerBase &PM, CodeGenOpt::Level OptLevel);
};

} // end namespace llvm

#endif
