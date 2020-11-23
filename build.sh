#!/bin/bash
#
# Script to build zynayumi on a GNU/Linux system.

set -x

# Build libzynayumi
cd libzynayumi
mkdir build
cd build
cmake ..
make -j
cd ../..

# Build zynayumi
make -j
