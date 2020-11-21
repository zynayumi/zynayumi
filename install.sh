#!/bin/bash
#
# Script to build and install Zynayumi on a GNU/Linux system.

set -x

# Build
cd libzynayumi
mkdir build
cd build
cmake ..
make -j
cd ../..

# Install
cd bin
sudo cp zynayumi /usr/local/bin
sudo mkdir /usr/local/lib/lv2
sudo cp -r zynayumi.lv2 /usr/local/lib/lv2
sudo mkdir /usr/local/lib/dssi
sudo cp zynayumi-dssi.so /usr/local/lib/dssi
sudo mkdir /usr/local/lib/vst
sudo cp zynayumi-vst.so /usr/local/lib/vst
cd ..
