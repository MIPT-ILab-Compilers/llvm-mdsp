// RUN: %clang_cc1 -triple x86_64-apple-darwin10 -ftrapv %s -emit-llvm -o - | FileCheck %s

// CHECK: [[I32O:%.*]] = type { i32, i1 }

unsigned int ui, uj, uk;
int i, j, k;

// CHECK: define void @test0()
void test0() {
  // -ftrapv doesn't affect unsigned arithmetic.
  // CHECK:      [[T1:%.*]] = load i32* @uj
  // CHECK-NEXT: [[T2:%.*]] = load i32* @uk
  // CHECK-NEXT: [[T3:%.*]] = add i32 [[T1]], [[T2]]
  // CHECK-NEXT: store i32 [[T3]], i32* @ui
  ui = uj + uk;

  // CHECK:      [[T1:%.*]] = load i32* @j
  // CHECK-NEXT: [[T2:%.*]] = load i32* @k
  // CHECK-NEXT: [[T3:%.*]] = call [[I32O]] @llvm.sadd.with.overflow.i32(i32 [[T1]], i32 [[T2]])
  // CHECK-NEXT: [[T4:%.*]] = extractvalue [[I32O]] [[T3]], 0
  // CHECK-NEXT: [[T5:%.*]] = extractvalue [[I32O]] [[T3]], 1
  // CHECK-NEXT: br i1 [[T5]]
  // CHECK:      call void @llvm.trap()
  i = j + k;
}

// CHECK: define void @test1()
void test1() {
  extern void opaque(int);
  opaque(i++);

  // CHECK:      [[T1:%.*]] = load i32* @i
  // CHECK-NEXT: [[T2:%.*]] = call [[I32O]] @llvm.sadd.with.overflow.i32(i32 [[T1]], i32 1)
  // CHECK-NEXT: [[T3:%.*]] = extractvalue [[I32O]] [[T2]], 0
  // CHECK-NEXT: [[T4:%.*]] = extractvalue [[I32O]] [[T2]], 1
  // CHECK-NEXT: br i1 [[T4]]
  // CHECK:      call void @llvm.trap()
}

// CHECK: define void @test2()
void test2() {
  extern void opaque(int);
  opaque(++i);

  // CHECK:      [[T1:%.*]] = load i32* @i
  // CHECK-NEXT: [[T2:%.*]] = call [[I32O]] @llvm.sadd.with.overflow.i32(i32 [[T1]], i32 1)
  // CHECK-NEXT: [[T3:%.*]] = extractvalue [[I32O]] [[T2]], 0
  // CHECK-NEXT: [[T4:%.*]] = extractvalue [[I32O]] [[T2]], 1
  // CHECK-NEXT: br i1 [[T4]]
  // CHECK:      call void @llvm.trap()
}
