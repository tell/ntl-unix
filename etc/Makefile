include ../common.mk
include $(ROOT)/ntl-conf.mk

WORK_DIR := $(shell pwd)

all:
	$(MAKE) -C tfactortools -f $(WORK_DIR)/tfactortools-build.mk
	$(MAKE) -C benchtools -f $(WORK_DIR)/benchtools.mk

clean:
	$(MAKE) -C tfactortools -f $(WORK_DIR)/tfactortools-build.mk clean
	$(MAKE) -C benchtools -f $(WORK_DIR)/benchtools.mk clean
