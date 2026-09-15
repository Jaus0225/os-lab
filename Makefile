CC = gcc
CFLAGS = -Wall -Wextra -g -D_POSIX_C_SOURCE=200809L
BINDIR = bin

# Source files
SRC_FILES = $(wildcard src/*.c)
CH_FILES  = $(wildcard challenges/*.c)

# Binaries to create
SRC_BINS = $(patsubst src/%.c,$(BINDIR)/%,$(SRC_FILES))
CH_BINS  = $(patsubst challenges/%.c,$(BINDIR)/%,$(CH_FILES))

all: $(BINDIR) $(SRC_BINS) $(CH_BINS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: src/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR)/%: challenges/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BINDIR) build/ lab_report/*.png lab_report/*.pdf

.PHONY: all clean
