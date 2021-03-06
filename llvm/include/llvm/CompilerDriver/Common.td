//===- Common.td - Common definitions for LLVMC2  ----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains common definitions used in llvmc tool description files.
//
//===----------------------------------------------------------------------===//

class Tool<list<dag> l> {
      list<dag> properties = l;
}

// Possible Tool properties.

def in_language;
def out_language;
def output_suffix;
def command;
def out_file_option;
def in_file_option;
def join;
def sink;
def works_on_empty;
def actions;

// Possible option types.

def alias_option;
def switch_option;
def switch_list_option;
def parameter_option;
def parameter_list_option;
def prefix_option;
def prefix_list_option;

// Possible option properties.

def help;
def hidden;
def init;
def multi_val;
def one_or_more;
def zero_or_more;
def optional;
def really_hidden;
def required;
def comma_separated;
def forward_not_split;

// The 'case' construct.
def case;

// Boolean constants.
def true;
def false;

// Boolean operators.
def and;
def or;
def not;

// Primitive tests.
def switch_on;
def parameter_equals;
def element_in_list;
def input_languages_contain;
def empty;
def not_empty;
def default;
def single_input_file;
def multiple_input_files;
def any_switch_on;
def any_not_empty;
def any_empty;

// Possible actions.

def append_cmd;
def forward;
def forward_as;
def forward_value;
def forward_transformed_value;
def stop_compilation;
def no_out_file;
def unpack_values;
def warning;
def error;
def set_option;
def unset_option;

// Increase the edge weight.
def inc_weight;

// Option list - a single place to specify options.
class OptionList<list<dag> l> {
      list<dag> options = l;
}

// Option preprocessor - actions taken during plugin loading.
class OptionPreprocessor<dag d> {
      dag preprocessor = d;
}

// Map from suffixes to language names

def lang_to_suffixes;

class LanguageMap<list<dag> l> {
      list<dag> map = l;
}

// Compilation graph

def edge;
def optional_edge;

class CompilationGraph<list<dag> l> {
      list<dag> edges = l;
}
