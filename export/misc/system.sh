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
	FILES=`${BETALIB}/export/files/system.files`
	echo "$FILES" | ${BETALIB}/export/misc/icomp $DST/system.cmd

echo "cd %BETALIB%"                                   >  $DST/system.new
echo "copy /Q bin\\README.txt README.txt"             >> $DST/system.new
echo ""                                               >> $DST/system.new
cat $DST/system.cmd                                   >> $DST/system.new
mv $DST/system.new  $DST/system.cmd

else

	echo ""
	echo "Creating $DST/system.tar.${ZEXT} "
	echo "(Listing in $DST/system.lst)"

	cd ${BETALIB}; 

	FILES=`${BETALIB}/export/files/system.files`

	tar -covhf -  $FILES \
	2> $DST/system.lst \
	| $COMPRESS >  $DST/system.tar.${ZEXT}
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack system