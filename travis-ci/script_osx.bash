#!/bin/bash
set -ev
make 2>&1 | cat -n | awk '{ print $1 }' | sed -n -e 's/[05]00$/*/p'
make check
