// Note: the run lines follow their respective tests, since line/column
// matter in this test.
#define nil (void*)0
@protocol FooTestProtocol
+ protocolClassMethod;
- protocolInstanceMethod : (int)value;
@end
@interface Foo <FooTestProtocol> {
  void *isa;
}
+ (int)classMethod1:a withKeyword:(int)b;
+ (void)classMethod2;
+ new;
- instanceMethod1;
@end

@interface Foo (FooTestCategory)
+ categoryClassMethod;
- categoryInstanceMethod;
@end

void func() {
  Foo *obj = [Foo new];
  [obj xx];
}

@interface MyClass { }
+ (int)MyClassMethod:(id)obj;
- (int)MyInstMethod:(id)x second:(id)y;
@end

@interface MySubClass : MyClass { }
+ (int)MySubClassMethod;
- (int)MySubInstMethod;
@end

@implementation MyClass 
+ (int)MyClassMethod:(id)obj {
  return 0;
}

+ (int)MyPrivateMethod {
  return 1;
}

- (int)MyInstMethod:(id)x second:(id)y {
  return 2;
}

- (int)MyPrivateInstMethod {
  return 3;
}
@end
MyClass *getMyClass();
@implementation MySubClass
+ (int)MySubClassMethod {
  return 2;
}

+ (int)MySubPrivateMethod {
  return [super MyPrivateMethod];
}

- (int)MySubInstMethod:(id)obj {
  return [super MyInstMethod: obj second:obj];
}

- (int)MyInstMethod:(id)x second:(id)y {
  return 3;
}
@end

void test_super_var(MySubClass *super) {
  [super MyInstMethod: super second:super];
}

@protocol FooTestProtocol2
- (int)secondProtocolInstanceMethod;
@end

void test_qual_id(id<FooTestProtocol,FooTestProtocol2> ptr) {
  [ptr protocolInstanceMethod:1];
}

@interface Overload
- (int)Method:(int)i;
- (int)Method;
- (int)Method:(float)f Arg1:(int)i1 Arg2:(int)i2;
- (int)Method:(float)f Arg1:(int)i1 OtherArg:(id)obj;
- (int)Method:(float)f SomeArg:(int)i1 OtherArg:(id)obj;
- (int)OtherMethod:(float)f Arg1:(int)i1 Arg2:(int)i2;
@end

void test_overload(Overload *ovl) {
  [ovl Method:1 Arg1:1 OtherArg:ovl];
}

@interface Ellipsis
- (int)Method:(int)i, ...; 
- (int)SentinelMethod:(int)i, ... __attribute__((sentinel(0,1)));
@end
void f(Ellipsis *e) {
  [e Method:1, 2, 3];
}

@interface Overload2
+ (int)Method:(int)i;
+ (int)Method;
+ (int)Method:(float)f Arg1:(int)i1 Arg2:(int)i2;
+ (int)Method:(float)f Arg1:(int)i1 OtherArg:(id)obj;
+ (int)Method:(float)f SomeArg:(int)i1 OtherArg:(id)obj;
+ (int)OtherMethod:(float)f Arg1:(int)i1 Arg2:(int)i2;
@end

void test_overload2(void) {
  [Overload2 Method:1 Arg1:1 OtherArg:ovl];
}

void msg_id(id x) {
  [x Method:1 Arg1:1 OtherArg:ovl];
  [[x blarg] Method:1 Arg1:1 OtherArg:ovl];
  [id Method:1 Arg1:1 OtherArg:ovl];
}

@interface A
- (void)method1;
@end 

@interface B : A
- (void)method2;
@end

void test_ranking(B *b) {
  [b method1];
  b method1];
}

void test_overload3(Overload *ovl) {
  ovl Method:1 Arg1:1 OtherArg:ovl];
   Overload2 Method:1 Arg1:1 OtherArg:ovl];
  (Overload2 Method:1 Arg1:1 OtherArg:ovl]);
}

@interface C : B
- (void)method2;
- (void)method3;
@end

void test_redundancy(C *c) {
  [c method2];
};

@protocol P
- (Class)class;
@end

@interface A () <P>
@end

@interface A ()
+ (void)class_method3;
@end

@interface A (Cat)
+ (void)class_method4;
@end

@implementation A
- (void)method5:(A*)a {
  [[self class] class_method4];
}
@end

void test_missing_open_more() {
  A *a = A class_method3];
}

// RUN: c-index-test -code-completion-at=%s:23:19 %s | FileCheck -check-prefix=CHECK-CC1 %s
// CHECK-CC1: {TypedText categoryClassMethod}
// CHECK-CC1: {TypedText classMethod1:}{Placeholder (id)}{HorizontalSpace  }{TypedText withKeyword:}{Placeholder (int)}
// CHECK-CC1: {TypedText classMethod2}
// CHECK-CC1: {TypedText new}
// CHECK-CC1: {TypedText protocolClassMethod}
// RUN: c-index-test -code-completion-at=%s:24:8 %s | FileCheck -check-prefix=CHECK-CC2 %s
// CHECK-CC2: {TypedText categoryInstanceMethod}
// CHECK-CC2: {TypedText instanceMethod1}
// CHECK-CC2: {TypedText protocolInstanceMethod:}{Placeholder (int)}
// RUN: c-index-test -code-completion-at=%s:61:16 %s | FileCheck -check-prefix=CHECK-CC3 %s
// CHECK-CC3: ObjCClassMethodDecl:{ResultType int}{TypedText MyClassMethod:}{Placeholder (id)}
// CHECK-CC3: ObjCClassMethodDecl:{ResultType int}{TypedText MyPrivateMethod}
// RUN: c-index-test -code-completion-at=%s:65:16 %s | FileCheck -check-prefix=CHECK-CC4 %s
// CHECK-CC4: ObjCInstanceMethodDecl:{ResultType int}{TypedText MyInstMethod:}{Placeholder (id)}{HorizontalSpace  }{TypedText second:}{Placeholder (id)}
// CHECK-CC4: ObjCInstanceMethodDecl:{ResultType int}{TypedText MyPrivateInstMethod}
// RUN: c-index-test -code-completion-at=%s:74:9 %s | FileCheck -check-prefix=CHECK-CC5 %s
// CHECK-CC5: ObjCInstanceMethodDecl:{ResultType int}{TypedText MyInstMethod:}{Placeholder (id)}{HorizontalSpace  }{TypedText second:}{Placeholder (id)}
// CHECK-CC5: ObjCInstanceMethodDecl:{ResultType int}{TypedText MySubInstMethod}
// RUN: c-index-test -code-completion-at=%s:82:8 %s | FileCheck -check-prefix=CHECK-CC6 %s
// CHECK-CC6: ObjCInstanceMethodDecl:{ResultType id}{TypedText protocolInstanceMethod:}{Placeholder (int)}
// CHECK-CC6: ObjCInstanceMethodDecl:{ResultType int}{TypedText secondProtocolInstanceMethod}
// RUN: c-index-test -code-completion-at=%s:95:8 %s | FileCheck -check-prefix=CHECK-CC7 %s
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method}
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (int)}
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText SomeArg:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CC7: ObjCInstanceMethodDecl:{ResultType int}{TypedText OtherMethod:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// RUN: c-index-test -code-completion-at=%s:95:17 %s | FileCheck -check-prefix=CHECK-CC8 %s
// CHECK-CC8: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// CHECK-CC8: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CC8: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{TypedText SomeArg:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CC8-NOT: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{TypedText }
// RUN: c-index-test -code-completion-at=%s:95:24 %s | FileCheck -check-prefix=CHECK-CC9 %s
// CHECK-CC9: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{Informative Arg1:}{TypedText Arg2:}{Placeholder (int)}
// CHECK-CC9: ObjCInstanceMethodDecl:{ResultType int}{Informative Method:}{Informative Arg1:}{TypedText OtherArg:}{Placeholder (id)}
// RUN: c-index-test -code-completion-at=%s:61:11 %s | FileCheck -check-prefix=CHECK-CCA %s
// CHECK-CCA: TypedefDecl:{TypedText Class}
// CHECK-CCA-NEXT: ObjCInterfaceDecl:{TypedText Foo}
// CHECK-CCA-NOT: FunctionDecl:{ResultType void}{TypedText func}{LeftParen (}{RightParen )}
// CHECK-CCA:FunctionDecl:{ResultType MyClass *}{TypedText getMyClass}{LeftParen (}{RightParen )}
// CHECK-CCA: TypedefDecl:{TypedText id}
// CHECK-CCA: ObjCInterfaceDecl:{TypedText MyClass}
// CHECK-CCA: ObjCInterfaceDecl:{TypedText MySubClass}
// CHECK-CCA: {ResultType Class}{TypedText self}
// CHECK-CCA: {TypedText super}
// RUN: c-index-test -code-completion-at=%s:103:6 %s | FileCheck -check-prefix=CHECK-CCB %s
// CHECK-CCB: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (int), ...}
// CHECK-CCB: ObjCInstanceMethodDecl:{ResultType int}{TypedText SentinelMethod:}{Placeholder (int), ...}{Text , nil}
// RUN: c-index-test -code-completion-at=%s:116:14 %s | FileCheck -check-prefix=CHECK-CCC %s
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText Method}
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (int)}
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (float)}{HorizontalSpace  }{TypedText SomeArg:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CCC: ObjCClassMethodDecl:{ResultType int}{TypedText OtherMethod:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// RUN: c-index-test -code-completion-at=%s:116:23 %s | FileCheck -check-prefix=CHECK-CCD %s
// CHECK-CCD: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// CHECK-CCD: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CCD: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{TypedText SomeArg:}{Placeholder (int)}{HorizontalSpace  }{TypedText OtherArg:}{Placeholder (id)}
// CHECK-CCD-NOT: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{TypedText }
// RUN: c-index-test -code-completion-at=%s:116:30 %s | FileCheck -check-prefix=CHECK-CCE %s
// CHECK-CCE: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{Informative Arg1:}{TypedText Arg2:}{Placeholder (int)}
// CHECK-CCE: ObjCClassMethodDecl:{ResultType int}{Informative Method:}{Informative Arg1:}{TypedText OtherArg:}{Placeholder (id)}
// RUN: c-index-test -code-completion-at=%s:61:11 %s | FileCheck -check-prefix=CHECK-CCF %s
// CHECK-CCF: TypedefDecl:{TypedText Class}
// CHECK-CCF: ObjCInterfaceDecl:{TypedText Foo}
// CHECK-CCF-NOT: FunctionDecl:{ResultType void}{TypedText func}{LeftParen (}{RightParen )}
// CHECK-CCF: TypedefDecl:{TypedText id}
// CHECK-CCF: ObjCInterfaceDecl:{TypedText MyClass}
// CHECK-CCF: ObjCInterfaceDecl:{TypedText MySubClass}
// CHECK-CCF: {ResultType Class}{TypedText self}
// CHECK-CCF: {TypedText super}
// RUN: c-index-test -code-completion-at=%s:120:6 %s | FileCheck -check-prefix=CHECK-CCG %s
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType id}{TypedText categoryInstanceMethod}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType id}{TypedText instanceMethod1}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType int}{TypedText Method}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType int}{TypedText MyInstMethod:}{Placeholder (id)}{HorizontalSpace  }{TypedText second:}{Placeholder (id)}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType int}{TypedText MyPrivateInstMethod}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType int}{TypedText MySubInstMethod}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType id}{TypedText protocolInstanceMethod:}{Placeholder (int)}
// CHECK-CCG: ObjCInstanceMethodDecl:{ResultType int}{TypedText secondProtocolInstanceMethod}
// RUN: c-index-test -code-completion-at=%s:121:14 %s | FileCheck -check-prefix=CHECK-CCG %s
// RUN: c-index-test -code-completion-at=%s:122:7 %s | FileCheck -check-prefix=CHECK-CCH %s
// CHECK-CCH: ObjCClassMethodDecl:{ResultType id}{TypedText categoryClassMethod}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText classMethod1:}{Placeholder (id)}{HorizontalSpace  }{TypedText withKeyword:}{Placeholder (int)}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType void}{TypedText classMethod2}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText Method}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText Method:}{Placeholder (int)}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText MyClassMethod:}{Placeholder (id)}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText MyPrivateMethod}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText MySubClassMethod}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText MySubPrivateMethod}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType id}{TypedText new}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType int}{TypedText OtherMethod:}{Placeholder (float)}{HorizontalSpace  }{TypedText Arg1:}{Placeholder (int)}{HorizontalSpace  }{TypedText Arg2:}{Placeholder (int)}
// CHECK-CCH: ObjCClassMethodDecl:{ResultType id}{TypedText protocolClassMethod}
// RUN: c-index-test -code-completion-at=%s:134:6 %s | FileCheck -check-prefix=CHECK-CCI %s
// CHECK-CCI: ObjCInstanceMethodDecl:{ResultType void}{TypedText method1} (37)
// CHECK-CCI: ObjCInstanceMethodDecl:{ResultType void}{TypedText method2} (35)

// RUN: c-index-test -code-completion-at=%s:150:5 %s | FileCheck -check-prefix=CHECK-REDUNDANT %s
// CHECK-REDUNDANT: ObjCInstanceMethodDecl:{ResultType void}{TypedText method2} (35)
// CHECK-REDUNDANT-NOT: ObjCInstanceMethodDecl:{ResultType void}{TypedText method2}
// CHECK-REDUNDANT: ObjCInstanceMethodDecl:{ResultType void}{TypedText method3} (35)

// RUN: c-index-test -code-completion-at=%s:170:16 %s | FileCheck -check-prefix=CHECK-CLASS-RESULT %s
// CHECK-CLASS-RESULT: ObjCClassMethodDecl:{ResultType void}{TypedText class_method3} (35)
// CHECK-CLASS-RESULT: ObjCClassMethodDecl:{ResultType void}{TypedText class_method4} (35)

// Test code completion with a missing opening bracket:
// RUN: c-index-test -code-completion-at=%s:135:5 %s | FileCheck -check-prefix=CHECK-CCI %s
// RUN: c-index-test -code-completion-at=%s:139:7 %s | FileCheck -check-prefix=CHECK-CC7 %s
// RUN: c-index-test -code-completion-at=%s:139:16 %s | FileCheck -check-prefix=CHECK-CC8 %s
// RUN: c-index-test -code-completion-at=%s:139:23 %s | FileCheck -check-prefix=CHECK-CC9 %s

// RUN: c-index-test -code-completion-at=%s:140:14 %s | FileCheck -check-prefix=CHECK-CCC %s
// RUN: c-index-test -code-completion-at=%s:140:23 %s | FileCheck -check-prefix=CHECK-CCD %s
// RUN: c-index-test -code-completion-at=%s:140:30 %s | FileCheck -check-prefix=CHECK-CCE %s
// RUN: c-index-test -code-completion-at=%s:141:14 %s | FileCheck -check-prefix=CHECK-CCC %s
// RUN: c-index-test -code-completion-at=%s:141:23 %s | FileCheck -check-prefix=CHECK-CCD %s
// RUN: c-index-test -code-completion-at=%s:141:30 %s | FileCheck -check-prefix=CHECK-CCE %s

// RUN: c-index-test -code-completion-at=%s:175:12 %s | FileCheck -check-prefix=CHECK-CLASS-RESULT %s
