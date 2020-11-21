#!/bin/bash
#
# Script to uninstall Zynayumi on a GNU/Linux system that has been
# prevoously installed with install.sh.

set -x

# Uninstall
sudo rm /usr/local/bin/zynayumi
sudo rm -r /usr/local/lib/lv2/zynayumi.lv2
sudo rm /usr/local/lib/dssi/zynayumi-dssi.so
sudo rm /usr/local/lib/vst/zynayumi-vst.so
