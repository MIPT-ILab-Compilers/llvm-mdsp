// RUN: %llvmgxx -S %s -o - | grep noalias

void foo(int * __restrict myptr1, int * myptr2) {
  myptr1[0] = 0;
  myptr2[0] = 0;
}
