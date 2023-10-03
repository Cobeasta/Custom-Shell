
.SHELLFLAGS := -c
CC = gcc
LDLIBS=-lncurses -lreadline
# directories
SRCDIR = src
ODIR = build
BINDIR = bin
# targets
SRC_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(patsubst $(SRCDIR)/%.c,$(ODIR)/%.o, $(SRC_FILES))
.PHONY: all clean

all: directories target
# output files
$(ODIR)/%.o: $(SRCDIR)/%.c
	$(info "Compile target")
	$(CC) -c -o $@ $< $(LDLIBS)

# Link into binary
target: $(OBJ_FILES)
	$(info "Binary target")
	$(CC) -o $(BINDIR)/shell $(OBJ_FILES) $(LDLIBS)

# Create directories
directories:
	echo shell is $(SHELL)
	$(mkdir -p $(ODIR))
	$(mkdir -p $(BINDIR))
clean:
	$(info "clean target")
	rm -f $(OBJ)

