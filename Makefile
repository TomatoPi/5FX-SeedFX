# Project Name
TARGET = 5FX-SeedFX

# Sources
CPP_SOURCES = src/err/err.cpp\
	5FX-SeedFX2.cpp

# Library Locations
LIBDAISY_DIR = ../../libdaisy
DAISYSP_DIR = ../../DaisySP

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile