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
	echo "Creating $DST/lib.cmd"
	FILES=`${BETALIB}/export/files/lib.files` 
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/lib.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/lib.pack"
        echo "echo 'Doing lib ...'" >>$DST/mac.pack
        echo "lib.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/lib.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/lib.pack
else

	echo ""
	echo "Creating $DST/lib.tar.${ZEXT} "
	echo "(Listing in $DST/lib.lst)"

	FILES=`${BETALIB}/export/files/lib.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/lib.lst \
	| $COMPRESS >  $DST/lib.tar.${ZEXT}
fi
fi
. ${BETALIB}/export/misc/check_problems.sh
check_pack lib