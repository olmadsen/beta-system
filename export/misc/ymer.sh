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
	echo "Creating $DST/ymer.cmd"
	FILES=`${BETALIB}/export/files/ymer.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/ymer.cmd

else

	echo ""
	echo "Creating $DST/ymer.tar.${ZEXT} "
	echo "(Listing in $DST/ymer.lst)"

	FILES=`${BETALIB}/export/files/ymer.files`

	cd ${BETALIB}; 

	tar -covhf -  $FILES \
	2> $DST/ymer.lst \
	| $COMPRESS >  $DST/ymer.tar.${ZEXT}
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack ymer