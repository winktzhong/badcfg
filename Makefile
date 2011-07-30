#
# Makefile for badcfg. It requires GNU Make.
#

PREFIX = /usr/local
LIBRARY = libbadcfg.a
BININSTALL = $(PREFIX)/bin
MANINSTALL = $(PREFIX)/man/man1
CFLAGS ?= -I. -g3 -std=c99 -pedantic -Wall -Wextra -Wno-long-long -Wno-unused-parameter

SOURCES = badcfg.c
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

HEADERS = $(wildcard *.h)

.PHONY: all
all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $(LIBRARY) $(OBJECTS)

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(OBJECTS)
	$(RM) -f $(LIBRARY)

