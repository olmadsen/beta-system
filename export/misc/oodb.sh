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
	FILES=`/users/beta/export/distribution/r3.1.1/files/oodb.files`
	echo "$FILES" | /users/beta/export/distribution/r3.1.1/misc/icomp $DST/oodb.cmd
else
	echo ""
	echo "Creating $DST/oodb.tar.${ZEXT} "
	echo "(Listing in $DST/oodb.lst)"

	FILES=`/users/beta/export/distribution/r3.1.1/files/oodb.files`

	cd /users/beta

	tar -covhf -  $FILES \
	2> $DST/oodb.lst \
	| $COMPRESS >  $DST/oodb.tar.${ZEXT}
fi

. /users/beta/export/distribution/r3.1.1/misc/check_problems.sh
check_pack oodb