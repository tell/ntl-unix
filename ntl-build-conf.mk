# Configurations for compilers:
CXXFLAGS = -std=c++11 -O2 -g3 -Wall -Wextra
# -fsanitize=address -fsanitize=leak -fsanitize=undefined
ifeq (Linux,$(shell uname -s))
CXXFLAGS += -pthread
endif
CC = $(CXX)
CFLAGS = $(CXXFLAGS)

NTL_ORIGINAL_DIR = $(ROOT)/ntl
NTL_DIR = $(ROOT)/ntl-build
define cmd.COPY_SRC
cp -r $(NTL_ORIGINAL_DIR) $(NTL_DIR)
endef

NTL_SRC = $(NTL_DIR)/src
NTL_ALL = $(NTL_SRC)/all
NTL_BUILD_TARGET = $(NTL_ALL)

ifeq (Darwin,$(shell uname -s))
  $(info Detected OS name: Darwin.)
  $(info Current NTL does not work on non-official toolchains, e.g., GCC in MacPorts.)
  CXX=/usr/bin/clang++
endif

define cmd.NTL_CONFIG
cd $(NTL_SRC) \
  && ./configure CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" PREFIX="$(NTL_ENV_DIR)" NTL_GMP_LIP=off
endef

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

define cmd.NTL_CHECK
$(MAKE) -C $(NTL_SRC) check
endef

define cmd.NTL_CLEAN
$(MAKE) -C $(NTL_SRC) clean; $(RM) $(NTL_ALL)
endef

$(NTL_SRC)/all:
	$(MAKE) -C $(NTL_SRC)
