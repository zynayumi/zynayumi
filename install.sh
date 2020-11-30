#!/bin/bash
#
# Script to install zynayumi on a GNU/Linux system.

set -x

# Constants
PREFIX="/usr/local"

# Install
cd bin
cp zynayumi "${PREFIX}/bin"
mkdir "${PREFIX}/lib/lv2"
cp -r zynayumi.lv2 "${PREFIX}/lib/lv2"
mkdir "${PREFIX}/lib/dssi"
cp zynayumi-dssi.so "${PREFIX}/lib/dssi"
mkdir "${PREFIX}/lib/vst"
cp zynayumi-vst.so "${PREFIX}/lib/vst"
cd ..
