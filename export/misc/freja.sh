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
	echo "Creating $DST/freja.cmd"
	FILES=`${BETALIB}/export/files/freja.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/freja.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/freja.pack"
        echo "echo 'Doing freja ...'" >>$DST/mac.pack
        echo "freja.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/freja.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/freja.pack
else
	echo ""
	echo "Creating $DST/freja.tar.${ZEXT} "
	echo "(Listing in $DST/freja.lst)"

	FILES=`${BETALIB}/export/files/freja.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/freja.lst \
	| $COMPRESS >  $DST/freja.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack freja