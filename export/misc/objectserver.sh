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
	echo "Creating $DST/objectserver.cmd"
	FILES=`/users/beta/export/distribution/r4.0/files/objectserver.files`
	echo "$FILES" | /users/beta/export/distribution/r4.0/misc/icomp $DST/objectserver.cmd
else
	echo ""
	echo "Creating $DST/objectserver.tar.${ZEXT} "
	echo "(Listing in $DST/objectserver.lst)"

	FILES=`/users/beta/export/distribution/r4.0/files/objectserver.files`

	cd /users/beta

	tar -covhf -  $FILES \
	2> $DST/objectserver.lst \
	| $COMPRESS >  $DST/objectserver.tar.${ZEXT}
fi