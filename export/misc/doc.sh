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
	echo "Creating $DST/doc.cmd"
	FILES=`${BETALIB}/export/files/doc.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/doc.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/doc.pack"
        echo "echo 'Doing doc ...'" >>$DST/mac.pack
        echo "doc.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/doc.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/doc.pack

else

	echo ""
	echo "Creating $DST/doc.tar.${ZEXT} "
	echo "(Listing in $DST/doc.lst)"

	FILES=`${BETALIB}/export/files/doc.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/doc.lst \
	| $COMPRESS >  $DST/doc.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack doc
