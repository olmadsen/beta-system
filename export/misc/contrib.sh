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
	echo "Creating $DST/contrib.cmd"
	FILES=`${BETALIB}/export/files/contrib.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/contrib.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/contrib.pack"
        echo "echo 'Doing contrib ...'" >>$DST/mac.pack
        echo "contrib.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/contrib.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/contrib.pack
else
	echo ""
	echo "Creating $DST/contrib.tar.${ZEXT} "
	echo "(Listing in $DST/contrib.lst)"

	FILES=`${BETALIB}/export/files/contrib.files`

	cd ${BETALIB}; 

	tar -covhf - $FILES \
	2> $DST/contrib.lst \
	| $COMPRESS >  $DST/contrib.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack contrib