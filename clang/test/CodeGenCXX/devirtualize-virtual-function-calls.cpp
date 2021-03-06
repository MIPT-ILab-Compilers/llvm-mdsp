// RUN: %clang_cc1 %s -emit-llvm -o - | FileCheck %s

struct A {
  virtual void f();
  
  A h();
};

A g();

void f(A a, A *ap, A& ar) {
  // This should not be a virtual function call.
  
  // CHECK: call void @_ZN1A1fEv(%struct.A* %a)
  a.f();

  // CHECK: call void %  
  ap->f();

  // CHECK: call void %  
  ar.f();
  
  // CHECK: call void @_ZN1A1fEv
  A().f();

  // CHECK: call void @_ZN1A1fEv
  g().f();
  
  // CHECK: call void @_ZN1A1fEv
  a.h().f();
}

struct B {
  virtual void f();
  ~B();
  
  B h();
};


void f() {
  // CHECK: call void @_ZN1B1fEv
  B().f();
  
  // CHECK: call void @_ZN1B1fEv
  B().h().f();
}
