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
	echo "Creating $DST/oodb.cmd"
	FILES=`${BETALIB}/export/files/oodb.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/oodb.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/oodb.pack"
        echo "echo 'Doing oodb ...'" >>$DST/mac.pack
        echo "oodb.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/oodb.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/oodb.pack
else
	echo ""
	echo "Creating $DST/oodb.tar.${ZEXT} "
	echo "(Listing in $DST/oodb.lst)"

	FILES=`${BETALIB}/export/files/oodb.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/oodb.lst \
	| $COMPRESS >  $DST/oodb.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack oodb