ROOT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
include $(ROOT)/common.mk
CXXFLAGS += -I$(PREFIX)/include
LDFLAGS += -L$(PREFIX)/lib
LOADLIBES += -lntl -lgmp
$(NTL_SRC)/all:
	$(MAKE) -C $(NTL_SRC)
