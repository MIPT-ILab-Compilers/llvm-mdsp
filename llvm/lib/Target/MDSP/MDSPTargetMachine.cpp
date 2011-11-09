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
#include "MDSPTargetMachine.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetRegistry.h"
#include "llvm/Module.h"

using namespace llvm;


//extern "C" void LLVMInitializeMDSPTargetInfo ()
//{
//	 RegisterTarget<Triple::mdsp, false> X(TheMDSPTarget, "mdsp", "MDSP");
//}

/// MDSPTargetMachine ctor - Create an ILP32 architecture model

MDSPTargetMachine::MDSPTargetMachine (const Target &T, const std::string &TT,
									  const std::string &FS)
  : llvm::LLVMTargetMachine	(T, TT),
    DataLayout			("e-P:32:32-F128:128:128")
    //Subtarget(TT, FS, is64bit),

  //  TLInfo(*this), TSInfo(*this), InstrInfo(Subtarget),
   // FrameLowering(Subtarget)
{
}


extern "C" void LLVMInitializeMDSPTarget()
{
  // Register the target.
  RegisterTargetMachine <MDSPTargetMachine> X(TheMDSPTarget);
}

