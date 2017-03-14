include common.mk
include $(ROOT)/ntl-conf.mk

.PHONY: all aux clean check install
.DEFAULT_GOAL := all

all: config.done patch.done $(NTL_BUILD_TARGET)

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

patch.done:
	./patch-script.sh
	touch $@

include ntl-dep.mk
