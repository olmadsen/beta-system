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
	echo "Creating $DST/betacl.cmd"
	FILES=`/users/beta/export/distribution/r3.1.1/files/betacl.files`
	echo "$FILES" | /users/beta/export/distribution/r3.1.1/misc/icomp $DST/betacl.cmd
else
	echo ""
	echo "Creating $DST/betacl.tar.${ZEXT}"
	echo "(Listing is in $DST/betacl.lst)"

	FILES=`/users/beta/export/distribution/r3.1.1/files/betacl.files`

	cd /users/beta
	
	tar -covhf -  $FILES \
	2> $DST/betacl.lst \
	| $COMPRESS >  $DST/betacl.tar.${ZEXT}
fi

. /users/beta/export/distribution/r3.1.1/misc/check_problems.sh
check_pack betacl