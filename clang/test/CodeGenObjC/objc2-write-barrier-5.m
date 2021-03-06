// RUN: %clang_cc1 -triple x86_64-apple-darwin10 -fobjc-gc -emit-llvm -o %t %s
// RUN: grep objc_assign_ivar %t | count 0
// RUN: grep objc_assign_strongCast %t | count 5
// RUN: %clang_cc1 -x objective-c++ -triple x86_64-apple-darwin10 -fobjc-gc -emit-llvm -o %t %s
// RUN: grep objc_assign_ivar %t | count 0
// RUN: grep objc_assign_strongCast %t | count 5

@interface TestUnarchiver 
{
	void  *allUnarchivedObjects;
}
@end

@implementation TestUnarchiver

struct unarchive_list {
    int ifield;
    id *list;
};

- (id)init {
    (*((struct unarchive_list *)allUnarchivedObjects)).list = 0;
    ((struct unarchive_list *)allUnarchivedObjects)->list = 0;
    (**((struct unarchive_list **)allUnarchivedObjects)).list = 0;
    (*((struct unarchive_list **)allUnarchivedObjects))->list = 0;
    return 0;
}

@end
