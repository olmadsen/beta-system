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
	echo "Creating $DST/system.cmd"
	FILES=`/users/beta/export/distribution/r4.0.1/files/system.files`
	echo "$FILES" | /users/beta/export/distribution/r4.0.1/misc/icomp $DST/system.cmd

else

	echo ""
	echo "Creating $DST/system.tar.${ZEXT} "
	echo "(Listing in $DST/system.lst)"

	cd ${BETALIB}; echo cd ${BETALIB}

	FILES=`/users/beta/export/distribution/r4.0.1/files/system.files`

	tar -covhf -  $FILES \
	2> $DST/system.lst \
	| $COMPRESS >  $DST/system.tar.${ZEXT}
fi

. /users/beta/export/distribution/r4.0.1/misc/check_problems.sh
check_pack system