#!/usr/bin/env bash

set -e

export NUM_JOBS=1

brew update;
brew install bash;
brew install lcov;

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_COVERAGE=ON
make UnitTests
lcov -c -i -d Tests/UnitTests -o base.info
bin/UnitTests
lcov -c -d Tests/UnitTests -o test.info
lcov -a base.info -a test.info -o coverage.info
lcov -r coverage.info '*/Toolchains/*' -o coverage.info
lcov -r coverage.info '*/Libraries/*' -o coverage.info
lcov -r coverage.info '*/Programs/*' -o coverage.info
lcov -r coverage.info '*/Tests/*' -o coverage.info
lcov -r coverage.info '*/Tools/*' -o coverage.info
lcov -l coverage.info
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"