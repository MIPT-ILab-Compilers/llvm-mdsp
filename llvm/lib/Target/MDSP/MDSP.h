//===-- MDSP.h - Top-level interface for MDSP representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// MDSP back-end.
//
//===----------------------------------------------------------------------===//

#ifndef MDSP_H
#define MDSP_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class MDSPTargetMachine;

  extern Target TheMDSPTarget;
} // end namespace llvm

// Defines symbolic names for MDSP registers.  This defines a mapping from
// register name to register number.
//
#include "MDSPGenRegisterNames.inc"

// Defines symbolic names for the MDSP instructions.
//
#include "MDSPGenInstrNames.inc"

#endif
