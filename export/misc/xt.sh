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
	echo "Creating $DST/xt.cmd"
	FILES=`${BETALIB}/export/files/xt.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/xt.cmd
else
	echo ""
	echo "Creating $DST/xt.tar.${ZEXT} "
	echo "(Listing in $DST/xt.lst)"

	FILES=`${BETALIB}/export/files/xt.files`

	cd ${BETALIB}; ; 

	tar -covhf -  $FILES \
	2> $DST/xt.lst \
	| $COMPRESS >  $DST/xt.tar.${ZEXT}
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack xt