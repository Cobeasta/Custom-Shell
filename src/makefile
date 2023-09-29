CC = gcc

LDLIBS=-lncurses
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
	$(CC) -c -o $@ $< $(LDLIBS)

# Link into binary
target: $(OBJ_FILES)
	$(CC) -o $(BINDIR)/main.exe $(OBJ_FILES)

# Create directories
directories:
	mkdir -p $(ODIR)
	mkdir -p $(BINDIR)
clean:
	rm -f $(OBJ)

