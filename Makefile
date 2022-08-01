### Makefile
### Automates the build and everything else of the project.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

include variables.mk

# Project
PROJECT = pecan

# Directories and Paths
SRCDIR      = src
EXTLIBDIR   = lib
BUILDDIR   := build
EXAMPLEDIR := example

# Fragments
TARGET    = $(BUILDDIR)/$(PROJECT)
LIBTARGET = $(BUILDDIR)/lib$(PROJECT).a
CFLAGS   += -I$(EXTLIBDIR)/cvector -I$(EXTLIBDIR)/microtar/src
SRCNAMES += main.c pecan.c attribute.c parser.c blob.c fileutils.c error.c
ifdef BUILD_GTK
	SRCNAMES += gtk/app.c
endif
SOURCES  += $(addprefix $(SRCDIR)/, $(SRCNAMES))
OBJECTS  := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
OBJECTS  += $(BUILDDIR)/microtar.o
ifdef BUILD_GTK
	OBJECTS += $(BUILDDIR)/gtk/gresources.o
endif

.PHONY: all compile run dbgcompile debug memcheck clean
all: $(TARGET)

compile: $(BUILDDIR)/stamp $(OBJECTS)

$(TARGET): compile
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

# TODO: Change this to only include SRCNAMES + microtar.
$(LIBTARGET): $(OBJECTS)
	$(AR) -rcs $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/stamp:
	$(MKDIR) $(@D)
ifdef BUILD_GTK
	$(MKDIR) $(@D)/gtk
endif
	$(TOUCH) $@

###
### Auxiliary Targets
###

run: $(TARGET)
	$(TARGET)

dbgcompile: CFLAGS += -g3 -DDEBUG
dbgcompile: clean $(TARGET)

debug: dbgcompile
	$(GDB) $(TARGET)

memcheck: CFLAGS += -DMEMCHECK
memcheck: dbgcompile
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all \
		--track-origins=yes --log-file=$(BUILDDIR)/valgrind.log $(TARGET)
	cat $(BUILDDIR)/valgrind.log

clean:
	$(RM) -r $(BUILDDIR)
ifdef BUILD_GTK
	$(RM) $(GTK_RESOURCES_TARGET)
endif

###
### MicroTAR External Library
###

$(BUILDDIR)/microtar.o: $(EXTLIBDIR)/microtar/src/microtar.c
	$(CC) $(CFLAGS) -c $< -o $@

###
### GTK Accessories
###

$(BUILDDIR)/gtk/gresources.o: $(GTK_RESOURCES_TARGET)
	$(CC) $(CFLAGS) -c $< -o $@

$(GTK_RESOURCES_TARGET): $(GTK_RESOURCES_SRC) $(GTK_RESOURCES_DEPS)
	$(GLIB_COMPILE_RESOURCES) $(GTK_RESOURCES_SRC) --target=$@ --sourcedir=$(GTK_RESOURCES_DIR) --generate-source

