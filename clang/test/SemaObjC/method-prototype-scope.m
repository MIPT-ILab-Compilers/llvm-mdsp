// RUN: %clang_cc1  -fsyntax-only -verify %s

// rdar://8877730

int object;

@class NSString, NSArray;

@interface Test 
- Func:(int)XXXX, id object;

- doSomethingElseWith:(id)object;

- (NSString *)doSomethingWith:(NSString *)object and:(NSArray *)object; // expected-warning {{redefinition of method parameter 'object'}} \
					  // expected-note {{previous declaration is here}}
@end

@implementation Test

- (NSString *)doSomethingWith:(NSString *)object and:(NSArray *)object // expected-warning {{redefinition of method parameter 'object'}} \
					  // expected-note {{previous declaration is here}}
{
    return object; // expected-warning {{incompatible pointer types returning 'NSArray *' from a function with result type 'NSString *'}}
}

- Func:(int)XXXX, id object { return object; }

- doSomethingElseWith:(id)object { return object; }

@end

struct P;

@interface Test1
- doSomethingWith:(struct S *)object and:(struct P *)obj; // expected-warning {{declaration of 'struct S' will not be visible outside of this function}}
@end

int obj;
