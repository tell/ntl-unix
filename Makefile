CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra

.PHONY: all clean config compile check

all: config compile check

clean:
	git clean -fd ntl
	git checkout ntl

config:
	cd ntl/src && ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)"

compile:
	cd ntl/src && make

check:
	cd ntl/src && make check
