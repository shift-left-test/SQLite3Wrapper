#!/bin/bash

cmake . -DCMAKE_BUILD_TYPE=Debug || exit 1
make all -j || exit 1
ctest --output-on-failure
make coverage
