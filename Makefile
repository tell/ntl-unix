PREFIX = $(shell pwd)/prefix
CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra
ifeq (Linux,$(shell uname -s))
CXXFLAGS += -pthread
CONFIG.cmd = ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)" NTL_THREADS=on
else
CONFIG.cmd = ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)"
endif

.PHONY: all clean check install

all: config.done ntl/src/all

clean:
	$(RM) *.done
	$(MAKE) -C ntl/src clean
	$(RM) ntl/src/all

check:
	$(MAKE) -C ntl/src check

install:
	$(MAKE) -C ntl/src install

config.done:
	cd ntl/src && $(CONFIG.cmd)
	touch $@

ntl/src/all:
	$(MAKE) -C ntl/src
