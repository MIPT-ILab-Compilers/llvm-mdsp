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
//#include "llvm/Module.h"

using namespace llvm;


/// MDSPTargetMachine ctor - Create an ILP32 architecture model

MDSPTargetMachine::MDSPTargetMachine (const Target &T, const std::string &TT, 
        const std::string &FS)
  :   LLVMTargetMachine(T, TT),
      DataLayout			("e-P:32:32-F128:128:128"), 
      TLInfo(*this), TSInfo(*this),
   // FrameLowering(Subtarget)
{
}


extern "C" void LLVMInitializeMDSPTarget()
{
  // Register the target.
  RegisterTargetMachine <MDSPTargetMachine> X(TheMDSPTarget);
  RegisterAsmInfo<MDSPELFMCAsmInfo> A(TheMDSPTarget);
}

