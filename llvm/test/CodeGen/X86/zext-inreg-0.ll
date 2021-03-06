; RUN: llc < %s -march=x86 | not grep and
; RUN: llc < %s -march=x86-64 > %t
; RUN: not grep and %t
; RUN: not grep movzbq %t
; RUN: not grep movzwq %t
; RUN: not grep movzlq %t

; These should use movzbl instead of 'and 255'.
; This related to not having a ZERO_EXTEND_REG opcode.

define i32 @a(i32 %d) nounwind  {
        %e = add i32 %d, 1
        %retval = and i32 %e, 255
        ret i32 %retval
}
define i32 @b(float %d) nounwind  {
        %tmp12 = fptoui float %d to i8
        %retval = zext i8 %tmp12 to i32
        ret i32 %retval
}
define i32 @c(i32 %d) nounwind  {
        %e = add i32 %d, 1
        %retval = and i32 %e, 65535
        ret i32 %retval
}
define i64 @d(i64 %d) nounwind  {
        %e = add i64 %d, 1
        %retval = and i64 %e, 255
        ret i64 %retval
}
define i64 @e(i64 %d) nounwind  {
        %e = add i64 %d, 1
        %retval = and i64 %e, 65535
        ret i64 %retval
}
define i64 @f(i64 %d) nounwind  {
        %e = add i64 %d, 1
        %retval = and i64 %e, 4294967295
        ret i64 %retval
}

define i32 @g(i8 %d) nounwind  {
        %e = add i8 %d, 1
        %retval = zext i8 %e to i32
        ret i32 %retval
}
define i32 @h(i16 %d) nounwind  {
        %e = add i16 %d, 1
        %retval = zext i16 %e to i32
        ret i32 %retval
}
define i64 @i(i8 %d) nounwind  {
        %e = add i8 %d, 1
        %retval = zext i8 %e to i64
        ret i64 %retval
}
define i64 @j(i16 %d) nounwind  {
        %e = add i16 %d, 1
        %retval = zext i16 %e to i64
        ret i64 %retval
}
define i64 @k(i32 %d) nounwind  {
        %e = add i32 %d, 1
        %retval = zext i32 %e to i64
        ret i64 %retval
}
