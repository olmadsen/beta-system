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
	echo "Creating $DST/bifrost.cmd"
	FILES=`/users/beta/export/distribution/r4.0.1/files/bifrost.files`
	echo "$FILES" | /users/beta/export/distribution/r4.0.1/misc/icomp $DST/bifrost.cmd
else
	echo ""
	echo "Creating $DST/bifrost.tar.${ZEXT} "
	echo "(Listing in $DST/bifrost.lst)"

	cd ${BETALIB}; echo cd ${BETALIB}

	FILES=`/users/beta/export/distribution/r4.0.1/files/bifrost.files`

	tar -covhf - $FILES \
	2> $DST/bifrost.lst \
	| $COMPRESS >  $DST/bifrost.tar.${ZEXT}
fi

. /users/beta/export/distribution/r4.0.1/misc/check_problems.sh
check_pack bifrost