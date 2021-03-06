; RUN: llc < %s -march=arm -mattr=+v5t | FileCheck %s

declare i32 @llvm.ctlz.i32(i32)

define i32 @test(i32 %x) {
; CHECK: test
; CHECK: clz r0, r0
        %tmp.1 = call i32 @llvm.ctlz.i32( i32 %x )
        ret i32 %tmp.1
}
