// RUN: %clang_cc1 -triple i386-unknown-unknown -mregparm 4 %s -emit-llvm -o %t
// RUN: FileCheck < %t %s

void f1(int a, int b, int c, int d,
        int e, int f, int g, int h);

void f0() {
// CHECK: call void @f1(i32 inreg 1, i32 inreg 2, i32 inreg 3, i32 inreg 4,
// CHECK: i32 5, i32 6, i32 7, i32 8)
  f1(1, 2, 3, 4, 5, 6, 7, 8);
}

// CHECK: declare void @f1(i32 inreg, i32 inreg, i32 inreg, i32 inreg,
// CHECK: i32, i32, i32, i32)

