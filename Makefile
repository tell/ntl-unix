include common.mk
include $(ROOT)/ntl-conf.mk

.PHONY: all aux clean check install
.DEFAULT_GOAL := all

all: config.done patch.done $(NTL_BUILD_TARGET)

aux:
	$(MAKE) -C $@

clean:
	$(RM) *.done
	$(call cmd.NTL_CLEAN)

check:
	$(call cmd.NTL_CHECK)

install:
	$(MAKE) -C $(NTL_SRC) install

copy.done:
	$(call cmd.COPY_SRC)
	touch $@

config.done: copy.done
	$(call cmd.NTL_CONFIG)
	touch $@

patch.done: patch.done
	env NTL_DIR=$(NTL_DIR) ./patch-script.sh
	touch $@
