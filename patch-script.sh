#!/bin/sh

sedcmd='sed'
if uname -s | grep 'Darwin' > /dev/null; then
	sedcmd='gsed'
fi

find ntl/ -name '*.c' -or -name '*.h' | xargs grep -lR 'gmp.h' | xargs $sedcmd -i '/#include <gmp\.h>/i\#include <stddef.h>'
