NTL_DIR = $(ROOT)/ntl
NTL_SRC = $(NTL_DIR)/src
NTL_ALL = $(NTL_SRC)/all

NTL_BUILD_TARGET = $(NTL_ALL)

NTL_CONFIG.cmd = cd $(NTL_SRC) && ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(PREFIX)" NTL_GMP_LIP=off

ifeq (1,$(USE_THREAD))
  NTL_CONFIG.cmd += NTL_THREADS=on
  $(info Use thread.)
else
  KERNEL_NAME = $(shell uname -s)
endif

ifneq (,$(findstring Linux,$(KERNEL_NAME)))
  $(info Kernel name contains Linux.)
  NTL_CONFIG.cmd += NTL_THREADS=on
  $(info Use thread.)
endif

ifneq (,$(findstring CYGWIN_NT,$(KERNEL_NAME)))
  $(info Kernel name contains CYGWIN_NT.)
  NTL_CONFIG.cmd += NTL_THREADS=on
  $(info Use thread.)
endif

NTL_CHECK.cmd = $(MAKE) -C $(NTL_SRC) check
NTL_CLEAN.cmd = $(MAKE) -C $(NTL_SRC) clean; $(RM) $(NTL_ALL)
