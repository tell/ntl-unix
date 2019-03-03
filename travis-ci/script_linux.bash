#!/bin/bash
set -ev
docker exec -ti $MY_NAME bash -c "cd $MY_TARGET_MOUNT; make" | cat -n | awk '{ print $1 }' | sed -n -e 's/[05]00$/*/p'
docker exec -ti $MY_NAME bash -c "cd $MY_TARGET_MOUNT; make check"
