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
	echo "Creating $DST/yggdrasil.cmd"
	FILES=`${BETALIB}/export/files/yggdrasil.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/yggdrasil.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/yggdrasil.pack"
        echo "echo 'Doing yggdrasil ...'" >>$DST/mac.pack
        echo "yggdrasil.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/yggdrasil.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/yggdrasil.pack
else
	echo ""
	echo "Creating $DST/yggdrasil.tar.${ZEXT} "
	echo "(Listing in $DST/yggdrasil.lst)"

	FILES=`${BETALIB}/export/files/yggdrasil.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/yggdrasil.lst \
	| $COMPRESS >  $DST/yggdrasil.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack yggdrasil