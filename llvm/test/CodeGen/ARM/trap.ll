; RUN: llc < %s -march=arm | FileCheck %s
; rdar://7961298

define void @t() nounwind {
entry:
; CHECK: t:
; CHECK: trap
  call void @llvm.trap()
  unreachable
}

declare void @llvm.trap() nounwind
