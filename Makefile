CC      ?= gcc
MKDIR_P ?= mkdir -p

# Library name
LIBRARY_NAME = event

# Configure directories
SRC_DIR  ?= src
INC_DIR  ?= include
OBJ_DIR  ?= obj
LIB_DIR  ?= lib
BLD_DIR  ?= build
TST_DIR  ?= tests
TST_DEPS ?= helper
EXT_DIR  ?= ext

LIBRARY  = $(LIB_DIR)/lib$(LIBRARY_NAME).a
HEADERS  = $(wildcard $(INC_DIR)/*.h)

# Locate all c files in the SRC dir and link them to their
# respective obj files
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Locate all c files in the TST dir and link them to their
# respective obj files
TST = $(wildcard $(TST_DIR)/*.c)
TST_OBJ = $(TST:$(TST_DIR)/%.c=$(OBJ_DIR)/%.o)
TST_SRC = $(wildcard $(TST_DIR)/test_*.c)
TST_EXE = $(TST_SRC:$(TST_DIR)/%.c=%)
TST_DEPS_OBJ = $(TST_DEPS:%=$(OBJ_DIR)/%.o)

#$(info [${TST_DEPS_OBJ}])


# FLAGS ------------------------------------------------------------------------

CPPFLAGS += -I$(INC_DIR) -I$(EXT_DIR)/fifo/include -I$(EXT_DIR)/list/include
CFLAGS   += -Wall
LDFLAGS  += -L$(LIB_DIR)
LDLIBS   += -l$(LIBRARY_NAME) -lfifo -llist


# MAKE RULES -------------------------------------------------------------------

library: $(LIBRARY)

# Run each test executable individually
$(TST_EXE): %: $(BLD_DIR)/%
	$(BLD_DIR)/$@
	
# Or all at the same time
test: $(TST_EXE)

all: library

clean:
		$(RM) $(SRC_OBJ) $(TST_OBJ) $(LIBRARY) $(TST_EXE:%=$(BLD_DIR)/%)

.PHONY: all clean $(TST_EXE)

# DIRECTORIES ------------------------------------------------------------------

$(OBJ_DIR):
	$(MKDIR_P) $@

$(BLD_DIR):
	$(MKDIR_P) $@


# BUILD LIBRARY ----------------------------------------------------------------

# Build the library object files
$(SRC_OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Link the library file
$(LIBRARY): $(SRC_OBJ)
	$(AR) rcs $@ $^
	
	
# BUILD EXTERNAL LIBRARIES -----------------------------------------------------

$(LIB_DIR)/lib%.a:
	$(MAKE) -C $(EXT_DIR)/$(@:$(LIB_DIR)/lib%.a=%) CC=$(CC) LIB_DIR=../../$(LIB_DIR)
	
	
# BUILD TESTS ------------------------------------------------------------------

# Build the test object files
$(TST_OBJ): $(OBJ_DIR)/%.o: $(TST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build the test executables
$(BLD_DIR)/test_%: $(OBJ_DIR)/test_%.o $(TST_DEPS_OBJ) $(LIBRARY)| $(BLD_DIR)
	$(CC) $(LDFLAGS) $< $(TST_DEPS_OBJ) $(LDLIBS) -o $@
