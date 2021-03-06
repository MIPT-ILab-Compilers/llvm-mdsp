; RUN: opt < %s -basicaa -gvn -instcombine -S |& FileCheck %s

target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:128:128"

; Make sure that basicaa thinks R and r are must aliases.
define i32 @test1(i8 * %P) {
entry:
	%Q = bitcast i8* %P to {i32, i32}*
	%R = getelementptr {i32, i32}* %Q, i32 0, i32 1
	%S = load i32* %R

	%q = bitcast i8* %P to {i32, i32}*
	%r = getelementptr {i32, i32}* %q, i32 0, i32 1
	%s = load i32* %r

	%t = sub i32 %S, %s
	ret i32 %t
; CHECK: @test1
; CHECK: ret i32 0
}

define i32 @test2(i8 * %P) {
entry:
	%Q = bitcast i8* %P to {i32, i32, i32}*
	%R = getelementptr {i32, i32, i32}* %Q, i32 0, i32 1
	%S = load i32* %R

	%r = getelementptr {i32, i32, i32}* %Q, i32 0, i32 2
  store i32 42, i32* %r

	%s = load i32* %R

	%t = sub i32 %S, %s
	ret i32 %t
; CHECK: @test2
; CHECK: ret i32 0
}


; This was a miscompilation.
define i32 @test3({float, {i32, i32, i32}}* %P) {
entry:
  %P2 = getelementptr {float, {i32, i32, i32}}* %P, i32 0, i32 1
	%R = getelementptr {i32, i32, i32}* %P2, i32 0, i32 1
	%S = load i32* %R

	%r = getelementptr {i32, i32, i32}* %P2, i32 0, i32 2
  store i32 42, i32* %r

	%s = load i32* %R

	%t = sub i32 %S, %s
	ret i32 %t
; CHECK: @test3
; CHECK: ret i32 0
}


;; This is reduced from the SmallPtrSet constructor.
%SmallPtrSetImpl = type { i8**, i32, i32, i32, [1 x i8*] }
%SmallPtrSet64 = type { %SmallPtrSetImpl, [64 x i8*] }

define i32 @test4(%SmallPtrSet64* %P) {
entry:
  %tmp2 = getelementptr inbounds %SmallPtrSet64* %P, i64 0, i32 0, i32 1
  store i32 64, i32* %tmp2, align 8
  %tmp3 = getelementptr inbounds %SmallPtrSet64* %P, i64 0, i32 0, i32 4, i64 64
  store i8* null, i8** %tmp3, align 8
  %tmp4 = load i32* %tmp2, align 8
	ret i32 %tmp4
; CHECK: @test4
; CHECK: ret i32 64
}

; P[i] != p[i+1]
define i32 @test5(i32* %p, i64 %i) {
  %pi = getelementptr i32* %p, i64 %i
  %i.next = add i64 %i, 1
  %pi.next = getelementptr i32* %p, i64 %i.next
  %x = load i32* %pi
  store i32 42, i32* %pi.next
  %y = load i32* %pi
  %z = sub i32 %x, %y
  ret i32 %z
; CHECK: @test5
; CHECK: ret i32 0
}

; P[i] != p[(i*4)|1]
define i32 @test6(i32* %p, i64 %i1) {
  %i = shl i64 %i1, 2
  %pi = getelementptr i32* %p, i64 %i
  %i.next = or i64 %i, 1
  %pi.next = getelementptr i32* %p, i64 %i.next
  %x = load i32* %pi
  store i32 42, i32* %pi.next
  %y = load i32* %pi
  %z = sub i32 %x, %y
  ret i32 %z
; CHECK: @test6
; CHECK: ret i32 0
}

; P[1] != P[i*4]
define i32 @test7(i32* %p, i64 %i) {
  %pi = getelementptr i32* %p, i64 1
  %i.next = shl i64 %i, 2
  %pi.next = getelementptr i32* %p, i64 %i.next
  %x = load i32* %pi
  store i32 42, i32* %pi.next
  %y = load i32* %pi
  %z = sub i32 %x, %y
  ret i32 %z
; CHECK: @test7
; CHECK: ret i32 0
}

; P[zext(i)] != p[zext(i+1)]
; PR1143
define i32 @test8(i32* %p, i16 %i) {
  %i1 = zext i16 %i to i32
  %pi = getelementptr i32* %p, i32 %i1
  %i.next = add i16 %i, 1
  %i.next2 = zext i16 %i.next to i32
  %pi.next = getelementptr i32* %p, i32 %i.next2
  %x = load i32* %pi
  store i32 42, i32* %pi.next
  %y = load i32* %pi
  %z = sub i32 %x, %y
  ret i32 %z
; CHECK: @test8
; CHECK: ret i32 0
}

define i8 @test9([4 x i8] *%P, i32 %i, i32 %j) {
  %i2 = shl i32 %i, 2
  %i3 = add i32 %i2, 1
  ; P2 = P + 1 + 4*i
  %P2 = getelementptr [4 x i8] *%P, i32 0, i32 %i3

  %j2 = shl i32 %j, 2
  
  ; P4 = P + 4*j
  %P4 = getelementptr [4 x i8]* %P, i32 0, i32 %j2

  %x = load i8* %P2
  store i8 42, i8* %P4
  %y = load i8* %P2
  %z = sub i8 %x, %y
  ret i8 %z
; CHECK: @test9
; CHECK: ret i8 0
}

define i8 @test10([4 x i8] *%P, i32 %i) {
  %i2 = shl i32 %i, 2
  %i3 = add i32 %i2, 4
  ; P2 = P + 4 + 4*i
  %P2 = getelementptr [4 x i8] *%P, i32 0, i32 %i3
  
  ; P4 = P + 4*i
  %P4 = getelementptr [4 x i8]* %P, i32 0, i32 %i2

  %x = load i8* %P2
  store i8 42, i8* %P4
  %y = load i8* %P2
  %z = sub i8 %x, %y
  ret i8 %z
; CHECK: @test10
; CHECK: ret i8 0
}
