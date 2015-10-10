PREFIX = $(shell pwd)/prefix
CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra
CONFIG.cmd = ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)"

.PHONY: all clean check install

all: config.done compile.done

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

compile.done:
	cd ntl/src && $(MAKE)
	touch $@
