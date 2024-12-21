# Thomas Daley
# September 13, 2021

# A generic build template for C/C++ programs

# executable name
EXE = app

# C compiler
CC = gcc
# C++ compiler
CXX = g++
# linker
LD = g++

# C flags
CFLAGS = -Wall -Wextra -Werror --std=gnu99 -g3
# C++ flags
CXXFLAGS = 
# C/C++ flags
CPPFLAGS = -Wall
# dependency-generation flags
DEPFLAGS = -MMD -MP
# linker flags
LDFLAGS = -lpthread
# library flags
LDLIBS = 
# asan flags
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
# asan library flags
ASAN_LIBS  = -static-libasan
# optimization flags for performance testing
PERF_FLAGS = -O3

# build directories
BIN = bin
OBJ = obj
SRC = src

SOURCES := $(wildcard $(SRC)/*.c $(SRC)/*.cc $(SRC)/*.cpp $(SRC)/*.cxx)

OBJECTS := \
	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c)) \
	$(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(wildcard $(SRC)/*.cc)) \
	$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp)) \
	$(patsubst $(SRC)/%.cxx, $(OBJ)/%.o, $(wildcard $(SRC)/*.cxx))

# include compiler-generated dependency rules
DEPENDS := $(OBJECTS:.o=.d)

# compile C source
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c -o $@
# compile C++ source
COMPILE.cxx = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
# link objects
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) $(ASAN_FLAGS) $(ASAN_LIBS) $(OBJECTS) -o $@

.DEFAULT_GOAL = all

.PHONY: all
all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC) $(OBJ) $(BIN) $(OBJECTS)
	$(LINK.o)

$(SRC):
	mkdir -p $(SRC)

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(COMPILE.c) $<

$(OBJ)/%.o: $(SRC)/%.cc
	$(COMPILE.cxx) $<

$(OBJ)/%.o: $(SRC)/%.cpp
	$(COMPILE.cxx) $<

$(OBJ)/%.o: $(SRC)/%.cxx
	$(COMPILE.cxx) $<

# force rebuild
.PHONY: remake
remake: clean $(BIN)/$(EXE)

# execute the program
.PHONY: run
run: $(BIN)/$(EXE)
	./$(BIN)/$(EXE) $(FILE) $(TIME)

# performance testing build
.PHONY: performance
performance: CFLAGS := $(PERF_FLAGS)
performance: CXXFLAGS := $(PERF_FLAGS)
performance: CPPFLAGS := $(PERF_FLAGS)
performance: LDFLAGS := -lpthread
performance: clean $(BIN)/$(EXE)

# remove previous build and objects
.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPENDS)
	$(RM) $(BIN)/$(EXE)

# remove everything except source
.PHONY: reset
reset:
	$(RM) -r $(OBJ)
	$(RM) -r $(BIN)

-include $(DEPENDS)
