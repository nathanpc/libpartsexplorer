### Makefile
### Automates the build and everything else of the project.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

include variables.mk

# Project
PROJECT = partsexplorer
LIBEXT  = a

# Directories and Paths
SRCDIR      = src
EXTLIBDIR   = lib
TESTDIR     = test
BUILDDIR   := build
EXAMPLEDIR := example

# Fragments
TARGET   = $(BUILDDIR)/lib$(PROJECT).$(LIBEXT)
CFLAGS  += -I$(EXTLIBDIR)/cvector -I$(EXTLIBDIR)/microtar/src
SOURCES += $(SRCDIR)/partsexplorer.c $(SRCDIR)/attribute.c
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
OBJECTS += $(BUILDDIR)/microtar.o

.PHONY: all compile run test debug memcheck clean
all: compile test

compile: $(BUILDDIR)/stamp $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -rcs $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/stamp:
	$(MKDIR) $(@D)
	$(TOUCH) $@

###
### Auxiliary Targets
###

run: test

debug: CFLAGS += -g3 -DDEBUG
debug: clean run

memcheck: CFLAGS += -g3 -DDEBUG -DMEMCHECK
memcheck: clean run

clean:
	$(RM) -r $(BUILDDIR)
	$(RM) valgrind.log

###
### MicroTAR External Library
###

$(BUILDDIR)/microtar.o: $(EXTLIBDIR)/microtar/src/microtar.c
	$(CC) $(CFLAGS) -c $< -o $@

###
### Library Test Program
###

test: $(BUILDDIR)/test
	$(BUILDDIR)/test

$(BUILDDIR)/test: LDFLAGS += -L$(BUILDDIR)
$(BUILDDIR)/test: LDLIBS += -l$(PROJECT)
$(BUILDDIR)/test: $(BUILDDIR)/main.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILDDIR)/main.o: compile $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $@
