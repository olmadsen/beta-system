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
	# Special windows packing
	echo ""
	echo "Creating $DST/system.cmd"
	FILES=`/users/beta/export/distribution/r3.1.1/files/system-pe.files`
	echo "\
$FILES \
./betarun/v2.7/${TARGET}/%SDK%/betarun.lib \
./betarun/v2.7/${TARGET}/%SDK%/betarunv.lib\
" \
| /users/beta/export/distribution/r3.1.1/misc/icomp $DST/system.cmd

echo "cd %BETALIB%\\betarun\\v2.7\\${TARGET}\%SDK%" > $DST/system-pe.cmd
echo "ren  betarun.lib  betarun.lib.orig"          >> $DST/system-pe.cmd
echo "ren  betarunv.lib betarunv.lib.orig"         >> $DST/system-pe.cmd
echo "copy betarun.pe betarun.lib"                 >> $DST/system-pe.cmd
echo "copy betarun.pe betarunv.lib"                >> $DST/system-pe.cmd
echo ""                                            >> $DST/system-pe.cmd
cat $DST/system.cmd                                >> $DST/system-pe.cmd
echo ""                                            >> $DST/system-pe.cmd
echo ""                                            >> $DST/system-pe.cmd
echo "cd %BETALIB%\\betarun\\v2.7\\${TARGET}\%SDK%">> $DST/system-pe.cmd
echo "del betarun.lib"                             >> $DST/system-pe.cmd
echo "del betarunv.lib"                            >> $DST/system-pe.cmd
echo "ren betarunv.lib.orig betarunv.lib"          >> $DST/system-pe.cmd
echo "ren betarun.lib.orig  betarun.lib"           >> $DST/system-pe.cmd
echo "cd %BETALIB%"                                >> $DST/system-pe.cmd
mv $DST/system-pe.cmd  $DST/system.cmd

else
	
	echo ""
	echo "Creating $DST/system.tar "
	echo "(Listing in $DST/system.lst)"
	FILES=`/users/beta/export/distribution/r3.1.1/files/system-pe.files`

	cd /users/beta

	tar -covhf - $FILES \
	2> $DST/system.lst \
	 > $DST/system.tar

	cd /users/beta/test
	echo "Adding betarun.pe as betarun.o and betarunv.o from directory"
	pwd

	/bin/rm -rf betarun
	mkdir betarun
	mkdir betarun/v2.7
	mkdir betarun/v2.7/$TARGET
	cp /users/beta/betarun/v2.7/$TARGET/betarun.pe ./betarun/v2.7/$TARGET/betarun.o
	cp /users/beta/betarun/v2.7/$TARGET/betarun.pe ./betarun/v2.7/$TARGET/betarunv.o

	tar -rovhf $DST/system.tar \
	  ./betarun/v2.7/${TARGET}/betarun.o \
	  ./betarun/v2.7/${TARGET}/betarunv.o  \
	>> $DST/system.lst

	echo "Compressing..."
	if [ -f $DST/system.tar.${ZEXT} ]
	then
	   /bin/rm -f $DST/system.tar.${ZEXT}
	fi
	$COMPRESS $DST/system.tar

fi

. /users/beta/export/distribution/r3.1.1/misc/check_problems.sh
check_pack system