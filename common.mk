ROOT := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
PREFIX = $(ROOT)/prefix
$(info "The root directory: $(ROOT)")
