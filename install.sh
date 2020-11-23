#!/bin/bash
#
# Script to install zynayumi on a GNU/Linux system.

set -x

# Install
cd bin
cp zynayumi /usr/local/bin
mkdir /usr/local/lib/lv2
cp -r zynayumi.lv2 /usr/local/lib/lv2
mkdir /usr/local/lib/dssi
cp zynayumi-dssi.so /usr/local/lib/dssi
mkdir /usr/local/lib/vst
cp zynayumi-vst.so /usr/local/lib/vst
cd ..
