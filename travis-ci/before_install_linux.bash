#!/bin/bash
set -ev
docker pull $MY_TARGET_DIST
docker run --name $MY_NAME -v $TRAVIS_BUILD_DIR:$MY_TARGET_MOUNT -td $MY_TARGET_DIST /bin/bash
