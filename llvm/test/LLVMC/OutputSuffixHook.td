// Check that hooks can be invoked from 'output_suffix'.
// RUN: tblgen -I %p/../../include --gen-llvmc %s -o %t
// RUN: FileCheck -input-file %t %s
// RUN: %compile_cxx %t
// XFAIL: vg_leak

include "llvm/CompilerDriver/Common.td"

// CHECK: std::string MyHook()

def OptList : OptionList<[
(switch_option "dummy1", (help "none"))
]>;

def dummy_tool : Tool<[
(command "dummy_cmd"),
(in_language "dummy_lang"),
(out_language "dummy_lang"),
(actions (case
         // CHECK: hooks::MyHook()
         (switch_on "dummy1"), (output_suffix "$CALL(MyHook)")))
]>;

def DummyGraph : CompilationGraph<[(edge "root", "dummy_tool")]>;
