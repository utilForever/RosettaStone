#!/usr/bin/env bash

set -e

export NUM_JOBS=1

mkdir build
cd build
cmake ..
make
bin/UnitTests

unamestr=`uname`
if [[ "$unamestr" == 'Darwin' ]]; then
    echo "Disabling pip test for macOS"
else
    cd ..
    pip3 install --user -r requirements.txt
    pip3 install --user .
    python3 -m pytest ./Tests/PythonTests
fi