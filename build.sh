#!/bin/bash
#
# Script to build zynayumi on a GNU/Linux system.

set -x

# Build libzynayumi
cd libzynayumi
rm -r build &> /dev/null
mkdir build
cd build
cmake ..
make -j
cd ../..

# Build zynayumi
rm -r build &> /dev/null
make -j

# Postprocess LV2 presets
./floatify.sh
