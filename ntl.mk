ROOT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
include $(ROOT)/common.mk
CXXFLAGS += -I$(NTL_ENV_DIR)/include
LDFLAGS += -L$(NTL_ENV_DIR)/lib
LOADLIBES += -lntl -lgmp
