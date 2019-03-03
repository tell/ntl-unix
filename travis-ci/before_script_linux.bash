#!/bin/bash
set -ev
docker exec -ti $MY_NAME bash -c "echo $CC; $CC --version"
docker exec -ti $MY_NAME bash -c "echo $CXX; $CXX --version"
