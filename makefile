CXX := g++
MYDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR := src
BIN := $(MYDIR)
BUILDDIR := build
TARGET := main

SRCEXT := cpp
CXXFLAGS := -std=c++14 -Wall 
LIBS := 
INC := -I include

MODULES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o, $(notdir $(MODULES)))
OBJDIR = $(addprefix build/,$(OBJECTS))

COVER = $(addsuffix .gcov,$(MODULES))

all: $(TARGET).o

$(OBJDIR): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo OBJETO: $@
	$(shell mkdir -p $(BUILDDIR))
	$(CXX) $(INC) $(CXXFLAGS) -c $(MYDIR)/$< -o $(MYDIR)/$@
	@echo ""

$(TARGET).o: $(OBJDIR)
	@echo COMPILANDO MAIN
	$(CXX) $(INC) $(CXXFLAGS) $(OBJDIR) $(TARGET).cpp $(LIBS) -o $(BIN)$(TARGET)
	

run:
	@./main

clean:
	$(RM) -r build/* coverage/* *.gcda *.gcno *.gcov *.exe *.o bin/* tests/bin/* lcov_report

.PHONY: clean