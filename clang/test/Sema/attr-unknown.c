// RUN: %clang_cc1 -fsyntax-only -verify -Wunknown-attributes %s

int x __attribute__((foobar)); // expected-warning {{unknown attribute 'foobar' ignored}}
void z() __attribute__((bogusattr)); // expected-warning {{unknown attribute 'bogusattr' ignored}}
