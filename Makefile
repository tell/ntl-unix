CXXFLAGS = -Ofast -Wall -Wextra

.PHONY: all config compile check

all: config compile check

config:
	cd ntl/src && ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)"

compile:
	cd ntl/src && make

check:
	cd ntl/src && make check
