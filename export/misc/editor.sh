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
	echo "Creating $DST/editor.cmd"
	FILES=`${BETALIB}/export/files/editor.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/editor.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/editor.pack"
        echo "echo 'Doing editor ...'" >>$DST/mac.pack
        echo "editor.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/editor.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/editor.pack

else

	echo ""
	echo "Creating $DST/editor.tar.${ZEXT} "
	echo "(Listing in $DST/editor.lst)"

	FILES=`${BETALIB}/export/files/editor.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/editor.lst \
	| $COMPRESS >  $DST/editor.tar.${ZEXT}
fi
fi
. ${BETALIB}/export/misc/check_problems.sh
check_pack editor