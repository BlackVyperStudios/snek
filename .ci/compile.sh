#!/bin/bash
set -ex

CLEANUP()
{
    git reset --hard
    git clean -fdx
}

# compile gcc release
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Release

# compile gcc debug
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Debug

# compile clang release
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Release

# compile clang debug
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Debug
