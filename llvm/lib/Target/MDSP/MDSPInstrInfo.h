//===- MDSPInstrInfo.h - MDSP Instruction Information -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
// This file contains the MDSP implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef MDSPINSTRUCTIONINFO_H
#define MDSPINSTRUCTIONINFO_H

#include "llvm/Target/TargetInstrInfo.h"
#include "MDSPRegisterInfo.h"

namespace llvm {

class MDSPInstrInfo : public TargetInstrInfoImpl {
   const MDSPRegisterInfo RI;
   const MDSPSubtarget& Subtarget;
 public:
   explicit MDSPInstrInfo(MDSPSubtarget &ST);

   /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
   /// such, whenever a client has an instance of instruction info, it should
   /// always be able to get register info as well (through this method).
   ///
   virtual const MDSPRegisterInfo &getRegisterInfo() const { return RI; }

   /// isLoadFromStackSlot - If the specified machine instruction is a direct
   /// load from a stack slot, return the virtual or physical register number of
   /// the destination along with the FrameIndex of the loaded stack slot.  If
   /// not, return 0.  This predicate must return 0 if the instruction has
   /// any side effects other than loading from the stack slot.
   virtual unsigned isLoadFromStackSlot(const MachineInstr *MI,
                                        int &FrameIndex) const { return 0;}

   /// isStoreToStackSlot - If the specified machine instruction is a direct
   /// store to a stack slot, return the virtual or physical register number of
   /// the source reg along with the FrameIndex of the loaded stack slot.  If
   /// not, return 0.  This predicate must return 0 if the instruction has
   /// any side effects other than storing to the stack slot.
   virtual unsigned isStoreToStackSlot(const MachineInstr *MI,
                                       int &FrameIndex) const { return 0;}


   virtual bool AnalyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TBB,
                              MachineBasicBlock *&FBB,
                              SmallVectorImpl<MachineOperand> &Cond,
                              bool AllowModify = false) const { return false;}

   virtual unsigned RemoveBranch(MachineBasicBlock &MBB) const { return 0;}

   virtual unsigned InsertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
                                 MachineBasicBlock *FBB,
                                 const SmallVectorImpl<MachineOperand> &Cond,
                                 DebugLoc DL) const { return 0;}

   virtual void copyPhysReg(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator I, DebugLoc DL,
                            unsigned DestReg, unsigned SrcReg,
                            bool KillSrc) const { }

   virtual void storeRegToStackSlot(MachineBasicBlock &MBB,
                                    MachineBasicBlock::iterator MBBI,
                                    unsigned SrcReg, bool isKill, int FrameIndex,
                                    const TargetRegisterClass *RC,
                                    const TargetRegisterInfo *TRI) const { }

   virtual void loadRegFromStackSlot(MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator MBBI,
                                     unsigned DestReg, int FrameIndex,
                                     const TargetRegisterClass *RC,
                                     const TargetRegisterInfo *TRI) const {}

   unsigned getGlobalBaseReg(MachineFunction *MF) const;



};

}

#endif
