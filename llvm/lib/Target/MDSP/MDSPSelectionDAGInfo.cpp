//===-- MDSPSelectionDAGInfo.cpp - MDSP SelectionDAG Info ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file implements the MDSPSelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "mdsp-selectiondag-info"

#include "MDSPTargetMachine.h"

using namespace llvm;

MDSPSelectionDAGInfo::MDSPSelectionDAGInfo(const MDSPTargetMachine &TM)
  : TargetSelectionDAGInfo(TM) {
}

MDSPSelectionDAGInfo::~MDSPSelectionDAGInfo() {
}
