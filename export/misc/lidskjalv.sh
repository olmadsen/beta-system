#!/bin/sh


if [ -z "$TARGET" ]; then echo "TARGET not set"; exit 1 ;fi
MACHINE=`echo "$TARGET" | tr "[a-z]" "[A-Z]"`
export MACHINE

if [ -z "$DST" ]; then echo "DST not set"; exit 1 ;fi
if [ -z "$AST" ]; then echo "AST not set"; exit 1 ;fi
if [ -z "$ZEXT" ]; then echo "ZEXT not set"; exit 1 ;fi
if [ -z "$COMPRESS" ]; then echo "COMPRESS not set"; exit 1 ;fi

if [ "$COMPRESS" = "icomp" ]
then
	echo ""
	echo "Creating $DST/lidskjalv.cmd"
	FILES=`${BETALIB}/export/files/lidskjalv.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/lidskjalv.cmd

else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/lidskjalv.pack"
        echo "echo 'Doing lidskjalv ...'" >>$DST/mac.pack
        echo "lidskjalv.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/lidskjalv.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/lidskjalv.pack
else
	echo ""
	echo "Creating $DST/lidskjalv.tar.${ZEXT} "
	echo "(Listing in $DST/lidskjalv.lst)"

	FILES=`${BETALIB}/export/files/lidskjalv.files`
	if [ "$TARGET" = "mac" ]
	then
	  echo $0: packing \"macintosh\" too...
	  FILES="$FILES ./guienv/v1.2/private/macintosh"
	  FILES="$FILES ./guienv/v1.2/utils/private/macintosh"
	fi

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/lidskjalv.lst \
	| $COMPRESS >  $DST/lidskjalv.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack lidskjalv
