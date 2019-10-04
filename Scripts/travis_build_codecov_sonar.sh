#!/usr/bin/env bash

set -e

export TRAVIS_COMPILER=g++-7
export CXX=g++-7
export CXX_FOR_BUILD=g++-7
export CC=gcc-7
export CC_FOR_BUILD=gcc-7

export NUM_JOBS=1

sudo apt-get install -yq gcovr ggcov lcov curl

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_COVERAGE=ON
build-wrapper-linux-x86-64 --out-dir ../bw-output make UnitTests
lcov --gcov-tool /usr/bin/gcov-7 -c -i -d Tests/UnitTests -o base.info
bin/UnitTests
lcov --gcov-tool /usr/bin/gcov-7 -c -d Tests/UnitTests -o test.info
lcov --gcov-tool /usr/bin/gcov-7 -a base.info -a test.info -o coverage.info
lcov --gcov-tool /usr/bin/gcov-7 -r coverage.info '/usr/*' -o coverage.info
lcov --gcov-tool /usr/bin/gcov-7 -r coverage.info '*/Extensions/*' -o coverage.info
lcov --gcov-tool /usr/bin/gcov-7 -r coverage.info '*/Includes/*' -o coverage.info
lcov --gcov-tool /usr/bin/gcov-7 -r coverage.info '*/Libraries/*' -o coverage.info
lcov --gcov-tool /usr/bin/gcov-7 -l coverage.info

curl -s https://codecov.io/bash > .codecov
chmod +x .codecov
./.codecov

cd ..
sonar-scanner