//===-- MDSPSelectionDAGInfo.cpp - MDSP SelectionDAG Info ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the MDSPSelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#include "MDSPTargetMachine.h"
using namespace llvm;

MDSPSelectionDAGInfo::MDSPSelectionDAGInfo(const MDSPTargetMachine &TM)
  : TargetSelectionDAGInfo(TM) {
}

MDSPSelectionDAGInfo::~MDSPSelectionDAGInfo() {
}
