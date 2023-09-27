
CC = gcc
# directories
ODIR = build
BINDIR = bin
# targets
SRC = $(wildcard *.c)
OBJ_FILES = $(patsubst $(SRCDIR)/%.c,$(ODIR)/%.o,$(SRC))
OBJ = $(SRC:$(SRCDIR)/%.c=$(ODIR)/%.o)

.PHONY: all clean

all: directories target
# output files
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $<

# Link into binary
target: $(OBJ_FILES)
	$(CC) -o $(BINDIR)/main.exe $(OBJ_FILES)

# Create directories
directories:
	mkdir -p $(ODIR)
	mkdir -p $(BINDIR)
clean:
	rm -f $(OBJ)

