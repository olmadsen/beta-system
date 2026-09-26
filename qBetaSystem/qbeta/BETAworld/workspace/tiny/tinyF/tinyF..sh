#!/bin/bash
set -e
BASE="$1"
echo $BETALIB
BL="$BETALIB"
QB="$BL"/qBetaSystem
QBA="$QB"/VM/MAC-ARM
echo "$QBA"
as -g -arch arm64 -o tinyF.o tinyF..a  
ld -macos_version_min 26.0 \
   -o tinyF \
      tinyF.o \
      "$QBA"/Mac_ARM_lib.o \
   -lSystem \
   -syslibroot "$(xcrun --show-sdk-path)"
echo "Built tinyF"
