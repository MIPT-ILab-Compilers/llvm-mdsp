//===-- MDSPSelectionDAGInfo.h - MDSP SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the MDSP subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPELECTIONDAGINFO_H
#define MDSPSELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class MDSPTargetMachine;

class MDSPSelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  explicit MDSPSelectionDAGInfo(const MDSPTargetMachine &TM);
  ~MDSPSelectionDAGInfo();
};

}

#endif
