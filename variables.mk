### variables.mk
### Common variables used throught the project.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

# Environment
PLATFORM := $(shell uname -s)

# Tools
CC    = gcc
AR    = ar
RM    = rm -f
GDB   = gdb
MKDIR = mkdir -p
TOUCH = touch

# Handle OS X-specific tools.
ifeq ($(PLATFORM), Darwin)
	CC  = clang
	CXX = clang
	GDB = lldb
endif

# Flags
CFLAGS  = -Wall -Wextra -pedantic
LDFLAGS =

# Default toolkit for Linux.
ifeq ($(PLATFORM), Linux)
	BUILD_GTK := 3
endif

# GTK application.
ifdef BUILD_GTK
	CFLAGS += -DHAS_GUI -DUSE_GTK $(shell pkg-config --cflags gtk+-3.0)
	LDLIBS += $(shell pkg-config --libs gtk+-3.0)
endif

