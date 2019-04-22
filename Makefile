include common.mk
include $(ROOT)/ntl-build-conf.mk

.PHONY: all aux clean check install
.DEFAULT_GOAL := all

all:
	$(MAKE) config.done
	$(MAKE) patch.done
	$(MAKE) $(NTL_BUILD_TARGET)

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

FORCE:
patch.done: FORCE
	env NTL_DIR=$(NTL_DIR) ./patch-script.sh
	touch $@
