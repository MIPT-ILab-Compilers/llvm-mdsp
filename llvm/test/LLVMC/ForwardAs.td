// Check the fix for PR4159.
// http://llvm.org/bugs/show_bug.cgi?id=4159
// RUN: tblgen -I %p/../../include --gen-llvmc %s -o %t
// RUN: FileCheck -input-file %t %s
// RUN: %compile_cxx %t
// XFAIL: vg_leak

include "llvm/CompilerDriver/Common.td"

def OptList : OptionList<[(parameter_option "dummy", (help "dummmy"))]>;

def dummy_tool : Tool<[
(command "dummy_cmd"),
(in_language "dummy"),
(out_language "dummy"),
(actions (case
         // CHECK: "unique_name"));
         (not_empty "dummy"), (forward_as "dummy", "unique_name")))
]>;

def DummyGraph : CompilationGraph<[(edge "root", "dummy_tool")]>;
