//===- TableGen'erated file -------------------------------------*- C++ -*-===//
//
// Register Information Header Fragment
//
// Automatically generated file, do not edit!
//
//===----------------------------------------------------------------------===//

#include "llvm/Target/TargetRegisterInfo.h"
#include <string>

namespace llvm {

struct MDSPGenRegisterInfo : public TargetRegisterInfo {
  explicit MDSPGenRegisterInfo(int CallFrameSetupOpcode = -1, int CallFrameDestroyOpcode = -1);
  virtual int getDwarfRegNumFull(unsigned RegNum, unsigned Flavour) const;
  virtual int getDwarfRegNum(unsigned RegNum, bool isEH) const = 0;
  virtual bool needsStackRealignment(const MachineFunction &) const
     { return false; }
  unsigned getSubReg(unsigned RegNo, unsigned Index) const;
  unsigned getSubRegIndex(unsigned RegNo, unsigned SubRegNo) const;
  unsigned composeSubRegIndices(unsigned, unsigned) const;
};

namespace GPR { // Register classes
  enum {
    GPRRegClassID = 0
  };

  struct GPRClass : public TargetRegisterClass {
    GPRClass();
  };
  extern GPRClass	GPRRegClass;
  static TargetRegisterClass * const GPRRegisterClass = &GPRRegClass;
} // end of namespace MDSP

} // End llvm namespace 
