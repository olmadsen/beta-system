#!/bin/sh

if [ -z "$TARGET" ]; then echo "TARGET not set"; exit 1 ;fi
MACHINE=`echo "$TARGET" | tr "[a-z]" "[A-Z]"`
export MACHINE

if [ -z "${DST}" ]; then echo "DST not set"; exit 1 ;fi
if [ -z "$AST" ]; then echo "AST not set"; exit 1 ;fi
if [ -z "$ZEXT" ]; then echo "ZEXT not set"; exit 1 ;fi
if [ -z "$COMPRESS" ]; then echo "COMPRESS not set"; exit 1 ;fi

FILES=`${BETALIB}/export/files/${SRC}.files` 

if [ "$COMPRESS" = "icomp" ]
then
	echo ""
	echo "Creating ${DST}/${SRC}.cmd"
	if [ "$FILES" = "" ]
	then
	    echo " -- ${SRC} empty, skipped"
	    exit 0
	else
	    echo "$FILES" | ${BETALIB}/export/misc/icomp ${DST}/${SRC}.cmd
	fi

else
if [ "$COMPRESS" = "maccomp" ]
then
	echo ""
	echo "Creating ${DST}/${SRC}.pack"
	if [ "$FILES" = "" ]
	then
	    echo " -- ${SRC} empty, skipped"
	    exit 0
	else
	    echo "echo 'Doing ${SRC} ...'" >>${DST}/mac.pack
	    echo "${SRC}.pack"             >>${DST}/mac.pack
	    echo "$FILES" | ${BETALIB}/export/misc/maccomp ${DST}/${SRC}.pack
	fi
else

	echo ""
	echo "Creating ${DST}/${SRC}.tar.${ZEXT} "
	echo "(Listing in ${DST}/${SRC}.lst)"

	if [ "$FILES" = "" ]
	then
	    echo " -- ${SRC} empty, skipped"
	    exit 0
	else
	    cd ${BETALIB};
	    FILES=`ls -d $FILES | grep -v CVS | xargs`
	    echo $FILES > ${DST}/${SRC}.lst0
	    tar -covhf -  $FILES \
	    2> ${DST}/${SRC}.lst \
	    | $COMPRESS >  ${DST}/${SRC}.tar.${ZEXT}
	fi
fi
fi
. ${BETALIB}/export/misc/check_problems.sh
check_pack ${SRC}