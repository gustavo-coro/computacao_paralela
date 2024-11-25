EXE = app

# C compiler
CC = mpicc
# linker
LD = mpicc

# C flags
CFLAGS = -Wall -Wextra -Werror --std=gnu99 -g3
# dependency-generation flags
DEPFLAGS = -MMD -MP
# linker flags
LDFLAGS = -lpthread
# library flags
LDLIBS = 

# build directories
BIN = bin
OBJ = obj
SRC = src

SOURCES := $(wildcard $(SRC)/*.c)

OBJECTS := \
	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

# include compiler-generated dependency rules
DEPENDS := $(OBJECTS:.o=.d)

# compile C source
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@
# link objects
LINK.o = $(LD) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

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

# force rebuild
.PHONY: remake
remake: clean $(BIN)/$(EXE)

# execute the program
PROCS ?= 4

.PHONY: run
run: $(BIN)/$(EXE)
	mpirun -np $(PROCS) ./$(BIN)/$(EXE) $(FILE) $(TIME)

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
