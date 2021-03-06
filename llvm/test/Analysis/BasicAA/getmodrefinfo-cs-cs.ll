; RUN: opt < %s -basicaa -aa-eval -print-all-alias-modref-info -disable-output |& FileCheck %s


; CHECK: Just Ref: call void @ro() <-> call void @f0()

declare void @f0()
declare void @ro() readonly

define void @test0() {
  call void @f0()
  call void @ro()
  ret void
}

; CHECK: NoModRef:   call void @llvm.memset.p0i8.i64(i8* @A, i8 0, i64 1, i32 1, i1 false) <->   call void @llvm.memset.p0i8.i64(i8* @B, i8 0, i64 1, i32 1, i1 false)
; CHECK: NoModRef:   call void @llvm.memset.p0i8.i64(i8* @B, i8 0, i64 1, i32 1, i1 false) <->   call void @llvm.memset.p0i8.i64(i8* @A, i8 0, i64 1, i32 1, i1 false)

declare void @llvm.memset.i64(i8*, i8, i64, i32)

@A = external global i8
@B = external global i8
define void @test1() {
  call void @llvm.memset.i64(i8* @A, i8 0, i64 1, i32 1)
  call void @llvm.memset.i64(i8* @B, i8 0, i64 1, i32 1)
  ret void
}
