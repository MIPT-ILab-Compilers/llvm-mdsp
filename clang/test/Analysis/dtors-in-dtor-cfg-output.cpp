// RUN: %clang_cc1 -analyze -analyzer-checker=debug.DumpCFG -cfg-add-implicit-dtors %s 2>&1 | FileCheck %s
// XPASS: *

class A {
public:
  ~A() {}
};

class B : public virtual A {
public:
  ~B() {}
};

class C : public virtual A {
public:
  ~C() {}
};

class TestOrder : public C, public B, public virtual A {
  A a;
  int i;
  A *p;
public:
  ~TestOrder();
};

TestOrder::~TestOrder() {}

class TestArray {
  A a[2];
  A b[0];
public:
  ~TestArray();
};

TestArray::~TestArray() {}

// CHECK:  [ B2 (ENTRY) ]
// CHECK:     Predecessors (0):
// CHECK:     Successors (1): B1
// CHECK:  [ B1 ]
// CHECK:       1: this->a.~A() (Member object destructor)
// CHECK:       2: ~B() (Base object destructor)
// CHECK:       3: ~C() (Base object destructor)
// CHECK:       4: ~A() (Base object destructor)
// CHECK:     Predecessors (1): B2
// CHECK:     Successors (1): B0
// CHECK:  [ B0 (EXIT) ]
// CHECK:     Predecessors (1): B1
// CHECK:     Successors (0):
// CHECK:  [ B2 (ENTRY) ]
// CHECK:     Predecessors (0):
// CHECK:     Successors (1): B1
// CHECK:  [ B1 ]
// CHECK:       1: this->a.~A() (Member object destructor)
// CHECK:     Predecessors (1): B2
// CHECK:     Successors (1): B0
// CHECK:  [ B0 (EXIT) ]
// CHECK:     Predecessors (1): B1
// CHECK:     Successors (0):
