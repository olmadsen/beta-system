#!/bin/bash
set -e
BASE="$1"
echo $BETALIB
BL="$BETALIB"
QB="$BL"/qBetaSystem
QBA="$QB"/VM/MAC-ARM
echo "$QBA"
as -g -arch arm64 -o SimpleFunctions.o SimpleFunctions..a  
ld -macos_version_min 26.0 \
   -o SimpleFunctions \
      SimpleFunctions.o \
      "$QBA"/Mac_ARM_lib.o \
   -lSystem \
   -syslibroot "$(xcrun --show-sdk-path)"
echo "Built SimpleFunctions"
