#!/bin/bash
set -ex

CLEANUP()
{
    git reset --hard
    git clean -fdx
}
RUN_PROGRAMMS()
{
    # a list of all programs / targets compiled by this project
    # currently there are no programms that could run by semselves
}

# compile gcc release
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Release
RUN_PROGRAMMS

# compile gcc debug
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Debug
RUN_PROGRAMMS

# compile clang release
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Release
RUN_PROGRAMMS

# compile clang debug
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
CLEANUP
cmake -DCMAKE_INSTALL_PREFIX=./inst .
cmake --build . --config Debug
RUN_PROGRAMMS
