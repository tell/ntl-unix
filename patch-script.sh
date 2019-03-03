#!/bin/bash

sedcmd='sed'
if uname -s | grep 'Darwin' > /dev/null; then
    sedcmd='gsed'
fi

if [ ! -d "$NTL_DIR" ]; then
    echo A variable NTL_DIR is not refer a directory.
    exit 1
fi
find "$NTL_DIR" -name '*.c' -or -name '*.cpp' -or -name '*.h' | xargs grep -lR 'gmp.h' | xargs $sedcmd -i '/#include <gmp\.h>/i\#include <stddef.h>'
# vim : set expandtab ft=bash :
