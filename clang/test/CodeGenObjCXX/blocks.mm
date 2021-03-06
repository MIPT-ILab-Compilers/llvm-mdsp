// RUN: %clang_cc1 -x objective-c++ -fblocks -triple x86_64-apple-darwin %s
// rdar://8979379

@interface A
@end

@interface B : A
@end

void f(int (^bl)(B* b));

// Test1
void g() {
  f(^(A* a) { return 0; });
}

// Test2
void g1() {
  int (^bl)(B* b) = ^(A* a) { return 0; };
}

// Test3
@protocol NSObject;

void bar(id(^)(void));

void foo(id <NSObject>(^objectCreationBlock)(void)) {
    return bar(objectCreationBlock);
}

