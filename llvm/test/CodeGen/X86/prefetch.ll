; RUN: llc < %s -march=x86 -mattr=+sse | FileCheck %s

define void @t(i8* %ptr) nounwind  {
entry:
; CHECK: prefetcht2
; CHECK: prefetcht1
; CHECK: prefetcht0
; CHECK: prefetchnta
	tail call void @llvm.prefetch( i8* %ptr, i32 0, i32 1 )
	tail call void @llvm.prefetch( i8* %ptr, i32 0, i32 2 )
	tail call void @llvm.prefetch( i8* %ptr, i32 0, i32 3 )
	tail call void @llvm.prefetch( i8* %ptr, i32 0, i32 0 )
	ret void
}

declare void @llvm.prefetch(i8*, i32, i32) nounwind 
