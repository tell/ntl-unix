PREFIX = $(shell pwd)/prefix
BUILD_DIR = ntl/src
CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra

ifeq (Linux,$(shell uname -s))
CXXFLAGS += -pthread
CONFIG.cmd = ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)"
else
CONFIG.cmd = ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)"
endif

.PHONY: all clean check install

all: config.done $(BUILD_DIR)/all

clean:
	$(RM) *.done
	$(MAKE) -C $(BUILD_DIR) clean
	$(RM) $(BUILD_DIR)/all

check:
	$(MAKE) -C $(BUILD_DIR) check

install:
	$(MAKE) -C $(BUILD_DIR) install

config.done:
	cd $(BUILD_DIR) && $(CONFIG.cmd)
	touch $@

$(BUILD_DIR)/all:
	$(MAKE) -C $(BUILD_DIR)
