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
	FILES=`${BETALIB}/export/files/betacl.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/betacl.cmd
else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating $DST/betacl.pack"
        echo "echo 'Doing betacl ...'" >>$DST/mac.pack
        echo "betacl.pack"             >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/betacl.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/betacl.pack
else
	echo ""
	echo "Creating $DST/betacl.tar.${ZEXT}"
	echo "(Listing is in $DST/betacl.lst)"

	FILES=`${BETALIB}/export/files/betacl.files`

	cd ${BETALIB}; 
	
	tar -covhf -  $FILES \
	2> $DST/betacl.lst \
	| $COMPRESS >  $DST/betacl.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack betacl