#define OBSCURE(X) X
#define DECORATION

typedef int T;
void OBSCURE(func)(int x) {
  OBSCURE(T) DECORATION value;
}

#include "a.h"

#define A(X) X
#define B(X) A(X)

B(int x);

// RUN: c-index-test -cursor-at=%s:1:11 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-1 %s
// CHECK-1: macro definition=OBSCURE
// RUN: c-index-test -cursor-at=%s:2:14 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-2 %s
// CHECK-2: macro definition=DECORATION
// RUN: c-index-test -cursor-at=%s:5:7 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-3 %s
// CHECK-3: macro instantiation=OBSCURE:1:9
// RUN: c-index-test -cursor-at=%s:6:6 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-4 %s
// CHECK-4: macro instantiation=OBSCURE:1:9
// RUN: c-index-test -cursor-at=%s:6:19 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-5 %s
// CHECK-5: macro instantiation=DECORATION:2:9
// RUN: c-index-test -cursor-at=%s:9:10 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-6 %s
// CHECK-6: inclusion directive=a.h
// RUN: c-index-test -cursor-at=%s:14:1 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-7 %s
// CHECK-7: macro instantiation=B:12:9

// Same tests, but with "editing" optimizations
// RUN: env CINDEXTEST_EDITING=1 c-index-test -cursor-at=%s:1:11 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-1 %s
// RUN: env CINDEXTEST_EDITING=1 c-index-test -cursor-at=%s:2:14 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-2 %s
// RUN: env CINDEXTEST_EDITING=1 c-index-test -cursor-at=%s:5:7 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-3 %s
// RUN: env CINDEXTEST_EDITING=1 c-index-test -cursor-at=%s:9:10 -I%S/Inputs %s | FileCheck -check-prefix=CHECK-6 %s
