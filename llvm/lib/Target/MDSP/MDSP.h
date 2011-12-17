#ifndef MDSP_H
#define MDSP_H


#include "llvm/Target/TargetMachine.h"
namespace llvm {
  class MDSPTargetMachine;

  extern Target TheMDSPTarget;
} // end namespace llvm

#include "MDSPGenRegisterNames.inc"
#include "MDSPGenInstrNames.inc"

#endif
