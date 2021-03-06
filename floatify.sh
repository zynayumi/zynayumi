#!/bin/bash

# Replace integers by floats to workaround so possible incompatibility issues
PRESETS_FILE=bin/zynayumi.lv2/presets.ttl
sed 's/pset:value[[:space:]]\(-\?[[:digit:]]\+\)[[:space:]]/pset:value \1.0/' -i "${PRESETS_FILE}"
