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
	echo "Creating $DST/com.cmd"
	FILES=`${BETALIB}/export/files/com.files` 
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/com.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/com.pack"
        echo "echo 'Doing com ...'" >>$DST/mac.pack
        echo "com.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/com.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/com.pack
else

	echo ""
	echo "Creating $DST/com.tar.${ZEXT} "
	echo "(Listing in $DST/com.lst)"

	FILES=`${BETALIB}/export/files/com.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/com.lst \
	| $COMPRESS >  $DST/com.tar.${ZEXT}
fi
fi
. ${BETALIB}/export/misc/check_problems.sh
check_pack com