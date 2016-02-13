include ../../common.mk

CXXFLAGS += -I$(PREFIX)/include

all: tfactor
	$(info The ROOT: $(ROOT))
