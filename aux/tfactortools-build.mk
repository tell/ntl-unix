include ../../common.mk

CXXFLAGS += -I$(PREFIX)/include
LDFLAGS += -L$(PREFIX)/lib
LOADLIBES += -lntl -lgmp

all: tfactor
	$(info The ROOT: $(ROOT))
