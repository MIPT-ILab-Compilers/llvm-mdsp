// RUN: %llvmgcc -xc %s -S -o - | grep llvm.*address | count 4

void *test1() {
  return __builtin_return_address(1);
}
void *test2() {
  return __builtin_frame_address(0);
}
