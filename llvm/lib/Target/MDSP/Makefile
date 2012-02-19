##===- lib/Target/MDSP/Makefile ---------------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMMDSPCodeGen
TARGET = MDSP

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = MDSPGenRegisterInfo.h.inc MDSPGenRegisterNames.inc \
                MDSPGenRegisterInfo.inc MDSPGenInstrNames.inc \
                MDSPGenInstrInfo.inc MDSPGenAsmWriter.inc \
                MDSPGenDAGISel.inc MDSPGenSubtarget.inc MDSPGenCallingConv.inc

DIRS = TargetInfo

include $(LEVEL)/Makefile.common

