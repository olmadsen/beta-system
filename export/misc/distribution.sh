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
	echo "Creating $DST/distribution.cmd"
	FILES=`${BETALIB}/export/files/distribution.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/distribution.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/distribution.pack"
        echo "echo 'Doing distribution ...'" >>$DST/mac.pack
        echo "distribution.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/distribution.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/distribution.pack
else
	echo ""
	echo "Creating $DST/distribution.tar.${ZEXT} "
	echo "(Listing in $DST/distribution.lst)"

	FILES=`${BETALIB}/export/files/distribution.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/distribution.lst \
	| $COMPRESS >  $DST/distribution.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack distribution