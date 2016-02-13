include common.mk
include $(ROOT)/ntl.mk

CXXFLAGS = -std=c++11 -O4 -g3 -Wall -Wextra
ifeq (Linux,$(shell uname -s))
CXXFLAGS += -pthread
endif

.PHONY: all aux clean check install

all: config.done $(NTL_BUILD_TARGET)

aux:
	$(MAKE) -C $@

clean:
	$(RM) *.done
	$(NTL_CLEAN.cmd)

check:
	$(NTL_CHECK.cmd)

install:
	$(MAKE) -C $(NTL_SRC) install

config.done:
	$(NTL_CONFIG.cmd)
	touch $@

include ntl-dep.mk
