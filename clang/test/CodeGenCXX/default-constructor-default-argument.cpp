// RUN: %clang_cc1 %s -emit-llvm -o - | FileCheck %s

// Check that call to constructor for struct A is generated correctly.
struct A { A(int x = 2); };
struct B : public A {};
B x;

// CHECK: call void @_ZN1AC2Ei
