ROOT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
PREFIX = $(ROOT)/prefix

# Configurations for compilers:

CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra
ifeq (Linux,$(shell uname -s))
CXXFLAGS += -pthread
endif
CC = $(CXX)
CFLAGS = $(CXXFLAGS)