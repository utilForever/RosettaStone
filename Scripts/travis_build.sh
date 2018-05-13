#!/usr/bin/env bash

set -e

export NUM_JOBS=1

mkdir build
cd build
cmake ..
make
bin/UnitTests
