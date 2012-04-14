//===-- MDSPTargetMachine.cpp - Define TargetMachine for MDSP -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "MDSP.h"
#include "MDSPMCAsmInfo.h"
#include "MDSPTargetMachine.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetRegistry.h"
#include "llvm/Module.h"

using namespace llvm;

extern "C" void LLVMInitializeMDSPTarget()
{
  RegisterTargetMachine <MDSPTargetMachine> X(TheMDSPTarget);

  RegisterAsmInfo<MDSPMCAsmInfo> A(TheMDSPTarget);
}


/// MDSPTargetMachine ctor - Create an ILP32 architecture model

MDSPTargetMachine::MDSPTargetMachine (const Target &T, const std::string &TT,
									  const std::string &FS)
  : llvm::LLVMTargetMachine	(T, TT),
    Subtarget		(TT, FS),
    DataLayout		(Subtarget.getDataLayout()),
    TLInfo			(*this),
    TSInfo			(*this),
    InstrInfo 		(Subtarget),
    FrameLowering 	(Subtarget)
{
}

bool MDSPTargetMachine::addInstSelector(PassManagerBase &PM,
                                        CodeGenOpt::Level OptLevel)
{
	PM.add(::createMDSPISelDag(*this));
	return false;
}

bool MDSPTargetMachine::addPreEmitPass(PassManagerBase &PM,
                                       CodeGenOpt::Level OptLevel)
{
  return true;
}



