// RUN: %llvmgcc -S %s -o - | llvm-as -o /dev/null

typedef struct
{
  void *stack;
  unsigned size;
  unsigned avail;
} compile_stack_type;

void foo(void*);
void bar(compile_stack_type T, unsigned);

void test() {
  compile_stack_type CST;
  foo(&CST);

  bar(CST, 12);
}
