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
	echo "Creating $DST/mjolnertool.cmd"
	FILES=`${BETALIB}/export/files/mjolnertool.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/mjolnertool.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/mjolnertool.pack"
        echo "echo 'Doing mjolnertool ...'" >>$DST/mac.pack
        echo "mjolnertool.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/mjolnertool.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/mjolnertool.pack
else
	echo ""
	echo "Creating $DST/mjolnertool.tar.${ZEXT} "
	echo "(Listing in $DST/mjolnertool.lst)"

	FILES=`${BETALIB}/export/files/mjolnertool.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/mjolnertool.lst \
	| $COMPRESS >  $DST/mjolnertool.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack mjolnertool