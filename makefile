CC := g++
MYDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR := 
BIN :=
BUILDDIR := build
TARGET := main

SRCEXT := cpp
CFLAGS := -g -std=c++14 -Wall 
LIBS := 
INC := -I include -I third-party


MODULES = lex symbol cadeia prod gram utils
SOURCES = $(addsuffix .cpp,$(MODULES))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TESTS = $(addprefix test_,$(SOURCES))
TESTSEXE = $(addsuffix .exe,$(TESTS))
TESTSEXEDIR = $(addprefix /tests/bin/,$(TESTSEXE))
COVER = $(addsuffix .gcov,$(SOURCES))

SOURCEDIR = $(addprefix ,$(SOURCES))
OBJDIR = $(addprefix build/,$(OBJECTS))
TSTDIR = $(addprefix tests/test_,$(SOURCES))
TGTDIR = $(TARGET)

all: $(TGTDIR)

$(OBJDIR): build/%.o : %.cpp
	@echo ""
	@echo OBJETO: $@
	$(shell mkdir -p build)
	$(CC) $(INC) $(CFLAGS) -c $(patsubst build/%.o,%.cpp,$@) -o $@

$(TGTDIR): $(OBJDIR)
	@echo ""
	@echo COMPILANDO MAIN
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) $(TARGET).cpp $(LIBS) -o $(TGTDIR)

tester: $(TESTS)
$(TESTS): tests/test_%.o : tests/test_%.cpp
	$(shell mkdir -p tests)
	$(shell mkdir -p tests/bin)
	@echo ""
	@echo TESTE: $@
	$(CC) $(INC) $(T_CFLAGS) tests/$@ $(OBJDIR) -o tests/bin/$(patsubst %.cpp,%,$@)
	tests/bin/$(patsubst %.cpp,%,$@)
	$(RM) test_*.gcno

comp: $(TGTDIR)
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) $(TARGET).cpp $(LIBS) -o $(TGTDIR)
	# @./main

run:
	@./main

clean:
	$(RM) -r build/* coverage/* *.gcda *.gcno *.gcov *.exe *.o bin/* tests/bin/*

.PHONY: clean