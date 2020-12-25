CXX := g++
MYDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR := src
BIN := $(MYDIR)
BUILDDIR := build
TARGET := main

SRCEXT := cpp
CXXFLAGS := -g -std=c++14 -Wall 
LIBS := 
INC := -I include -I third-party

MODULES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o, $(notdir $(MODULES)))
OBJDIR = $(addprefix build/,$(OBJECTS))

TESTDIR := tests
TESTSBINDIR = $(TESTDIR)/bin
TESTS1 = $(wildcard $(TESTDIR)/test_*.cpp) 
TESTS2 = $(patsubst %.cpp, %.o, $(TESTS1))

COVER = $(addsuffix .gcov,$(SOURCES))

all: $(TARGET).o

$(OBJDIR): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo OBJETO: $@
	$(shell mkdir -p $(BUILDDIR))
	$(CXX) $(INC) $(CXXFLAGS) -c $(MYDIR)/$< -o $(MYDIR)/$@
	@echo ""

$(TARGET).o: $(OBJDIR)
	@echo COMPILANDO MAIN
	$(CXX) $(INC) $(CXXFLAGS) $(OBJDIR) $(TARGET).cpp $(LIBS) -o $(BIN)$(TARGET)

# make tester: compila e roda todos os testes da pasta tests
# make tests/test_[nome].o : compila esse teste específico
tester: $(TESTS2)
$(TESTS2): %.o : %.cpp
	$(shell mkdir -p $(TESTDIR))
	$(shell mkdir -p $(TESTSBINDIR))
	@echo TESTE: $<
	$(CXX) $(INC) $(CXXFLAGS) $< $(OBJDIR) -o $(TESTSBINDIR)/$(patsubst %.o,%,$(notdir $@))
	$(TESTSBINDIR)/$(patsubst %.o,%,$(notdir $@))
	$(RM) test_*.gcno
	@echo ""

comp: $(TGTDIR)
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) $(TARGET).cpp $(LIBS) -o $(TGTDIR)
	# @./main

run:
	@./main

clean:
	$(RM) -r build/* coverage/* *.gcda *.gcno *.gcov *.exe *.o bin/* tests/bin/*

.PHONY: clean