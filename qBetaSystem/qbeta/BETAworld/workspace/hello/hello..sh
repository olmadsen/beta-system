<<<<<<< HEAD
#!/bin/bash
set -e
BASE="$1"
echo $BETALIB
BL="$BETALIB"
QB="$BL"/qBetaSystem
QBA="$QB"/VM/MAC-ARM
echo "$QBA"
as -g -arch arm64 -o hello.o hello..a  
ld -macos_version_min 26.0 \
   -o hello \
      hello.o \
      "$QBA"/Mac_ARM_lib.o \
   -lSystem \
   -syslibroot "$(xcrun --show-sdk-path)"
echo "Built hello"
=======
#!/bin/bash
set -e
BASE="$1"
echo $BETALIB
BL="$BETALIB"
QB="$BL"/qBetaSystem
QBA="$QB"/VM/MAC-ARM
echo "$QBA"
as -g -arch arm64 -o hello.o hello..a
ld -macos_version_min 26.0 \
   -o hello\
      hello.o \
      "$QBA"/Mac_ARM_lib.o \
   -lSystem \
   -syslibroot "$(xcrun --show-sdk-path)"
echo "Built hello"
>>>>>>> 7d06fc147 (hello.sh wirh Mac newmlines)
