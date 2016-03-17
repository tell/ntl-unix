include ../../ntl.mk

MAIN_TARGETs = flint-mul flint-mulmod flint-mulmodprecon flint-sqrmod \
	flint-lmul flint-lmulmod flint-lmulmodprecon flint-lsqrmod \
	flint-zmul \
	flint-factor flint-lfactor

EXPERIMENT.cmd = for x in $^; do echo ./$$x; done

all: $(MAIN_TARGETs)
	$(EXPERIMENT.cmd)

clean:
	$(RM) $(MAIN_TARGETs)
