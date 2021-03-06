/* Note: the RUN lines are near the end of the file, since line/column
 matter for this test. */
@class MyClass;
@interface I1 
{
  id StoredProp3;
  int RandomIVar;
}
@property int Prop0;
@property int Prop1;
@property float Prop2;
@end

@interface I2 : I1
@property id Prop3;
@property id Prop4;
@end

@implementation I2
@synthesize Prop2, Prop1, Prop3 = StoredProp3;
@dynamic Prop4;
@end

@interface I3 : I2
@property id Prop3;
@end

id test(I3 *i3) {
  return i3.Prop3;
}

// RUN: c-index-test -code-completion-at=%s:20:13 %s | FileCheck -check-prefix=CHECK-CC1 %s
// CHECK-CC1: ObjCPropertyDecl:{ResultType int}{TypedText Prop0}
// CHECK-CC1: ObjCPropertyDecl:{ResultType int}{TypedText Prop1}
// CHECK-CC1: ObjCPropertyDecl:{ResultType float}{TypedText Prop2}
// CHECK-CC1: ObjCPropertyDecl:{ResultType id}{TypedText Prop3}
// CHECK-CC1: ObjCPropertyDecl:{ResultType id}{TypedText Prop4}
// RUN: c-index-test -code-completion-at=%s:20:20 %s | FileCheck -check-prefix=CHECK-CC2 %s
// CHECK-CC2: ObjCPropertyDecl:{ResultType int}{TypedText Prop0}
// CHECK-CC2: ObjCPropertyDecl:{ResultType int}{TypedText Prop1}
// CHECK-CC2-NEXT: ObjCPropertyDecl:{ResultType id}{TypedText Prop3}
// CHECK-CC2: ObjCPropertyDecl:{ResultType id}{TypedText Prop4}
// RUN: c-index-test -code-completion-at=%s:20:35 %s | FileCheck -check-prefix=CHECK-CC3 %s
// CHECK-CC3: ObjCIvarDecl:{ResultType int}{TypedText RandomIVar}
// CHECK-CC3: ObjCIvarDecl:{ResultType id}{TypedText StoredProp3}
// RUN: c-index-test -code-completion-at=%s:21:10 %s | FileCheck -check-prefix=CHECK-CC4 %s
// CHECK-CC4: ObjCPropertyDecl:{ResultType int}{TypedText Prop0}
// CHECK-CC4-NEXT: ObjCPropertyDecl:{ResultType id}{TypedText Prop4}

// RUN: c-index-test -code-completion-at=%s:29:13 %s | FileCheck -check-prefix=CHECK-CC5 %s
// CHECK-CC5: ObjCPropertyDecl:{ResultType int}{TypedText Prop0} (35)
// CHECK-CC5-NEXT: ObjCPropertyDecl:{ResultType int}{TypedText Prop1} (35)
// CHECK-CC5-NEXT: ObjCPropertyDecl:{ResultType float}{TypedText Prop2} (35)
// CHECK-CC5-NEXT: ObjCPropertyDecl:{ResultType id}{TypedText Prop3} (35)
// CHECK-CC5-NEXT: ObjCPropertyDecl:{ResultType id}{TypedText Prop4} (35)

// RUN: c-index-test -code-completion-at=%s:9:11 %s | FileCheck -check-prefix=CHECK-CC6 %s
// CHECK-CC6: ObjCInterfaceDecl:{TypedText MyClass} (50)

