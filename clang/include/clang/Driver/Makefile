CLANG_LEVEL := ../../..
BUILT_SOURCES = Options.inc CC1Options.inc CC1AsOptions.inc

TABLEGEN_INC_FILES_COMMON = 1

include $(CLANG_LEVEL)/Makefile

$(ObjDir)/Options.inc.tmp : Options.td OptParser.td $(TBLGEN) $(ObjDir)/.dir
	$(Echo) "Building Clang Driver Option tables with tblgen"
	$(Verb) $(TableGen) -gen-opt-parser-defs -o $(call SYSPATH, $@) $<

$(ObjDir)/CC1Options.inc.tmp : CC1Options.td OptParser.td $(TBLGEN) $(ObjDir)/.dir
	$(Echo) "Building Clang CC1 Option tables with tblgen"
	$(Verb) $(TableGen) -gen-opt-parser-defs -o $(call SYSPATH, $@) $<

$(ObjDir)/CC1AsOptions.inc.tmp : CC1AsOptions.td OptParser.td $(TBLGEN) $(ObjDir)/.dir
	$(Echo) "Building Clang CC1 Assembler Option tables with tblgen"
	$(Verb) $(TableGen) -gen-opt-parser-defs -o $(call SYSPATH, $@) $<
