#!/bin/bash
#
# Script to uninstall Zynayumi on a GNU/Linux system that has been
# prevoously installed with install.sh.

set -x

# Constants
PREFIX="/usr/local"

# Uninstall
sudo rm "${PREFIX}/bin/zynayumi"
sudo rm -r "${PREFIX}/lib/lv2/zynayumi.lv2"
sudo rm "${PREFIX}/lib/dssi/zynayumi-dssi.so"
sudo rm "${PREFIX}/lib/vst/zynayumi-vst.so"
