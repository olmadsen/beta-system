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
	echo "Creating $DST/freja.cmd"
	FILES=`/users/beta/export/distribution/r4.0/files/freja.files`
	echo "$FILES" | /users/beta/export/distribution/r4.0/misc/icomp $DST/freja.cmd
else
	echo ""
	echo "Creating $DST/freja.tar.${ZEXT} "
	echo "(Listing in $DST/freja.lst)"

	FILES=`/users/beta/export/distribution/r4.0/files/freja.files`

	cd /users/beta

	tar -covhf -  $FILES \
	2> $DST/freja.lst \
	| $COMPRESS >  $DST/freja.tar.${ZEXT}
fi

. /users/beta/export/distribution/r4.0/misc/check_problems.sh
check_pack freja