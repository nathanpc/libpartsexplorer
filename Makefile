### Makefile
### Automates the build and everything else of the project.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

include variables.mk

# Project
PROJECT = pecan
LIBEXT  = a

# Directories and Paths
SRCDIR      = src
EXTLIBDIR   = lib
BUILDDIR   := build
EXAMPLEDIR := example

# Fragments
TARGET    = $(BUILDDIR)/lib$(PROJECT).$(LIBEXT)
EXETARGET = $(BUILDDIR)/$(PROJECT)
CFLAGS   += -I$(EXTLIBDIR)/cvector -I$(EXTLIBDIR)/microtar/src
SRCNAMES += pecan.c attribute.c parser.c blob.c fileutils.c error.c
SOURCES  += $(addprefix $(SRCDIR)/, $(SRCNAMES))
OBJECTS  := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
OBJECTS  += $(BUILDDIR)/microtar.o

.PHONY: all compile run exec dbgcompile debug memcheck clean
all: $(EXETARGET)

compile: $(BUILDDIR)/stamp $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -rcs $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/stamp:
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(EXETARGET): LDFLAGS += -L$(BUILDDIR)
$(EXETARGET): LDLIBS += -l$(PROJECT)
$(EXETARGET): $(BUILDDIR)/main.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILDDIR)/main.o: compile $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $@

###
### Auxiliary Targets
###

run: $(EXETARGET)
	$(EXETARGET)

dbgcompile: CFLAGS += -g3 -DDEBUG
dbgcompile: clean $(EXETARGET)

debug: dbgcompile
	$(GDB) $(EXETARGET)

memcheck: CFLAGS += -DMEMCHECK
memcheck: dbgcompile
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all \
		--track-origins=yes --log-file=$(BUILDDIR)/valgrind.log $(EXETARGET)
	cat $(BUILDDIR)/valgrind.log

clean:
	$(RM) -r $(BUILDDIR)

###
### MicroTAR External Library
###

$(BUILDDIR)/microtar.o: $(EXTLIBDIR)/microtar/src/microtar.c
	$(CC) $(CFLAGS) -c $< -o $@
