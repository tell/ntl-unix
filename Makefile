include common.mk
include $(ROOT)/ntl-conf.mk

.PHONY: all aux clean check install

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
	find ntl/ -name '*.c' -or -name '*.h' | xargs grep -lR 'gmp.h' | xargs sed -i '/#include <gmp\.h>/i\#include <stddef.h>'
	touch $@

include ntl-dep.mk
