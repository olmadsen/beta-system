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
	FILES=`${BETALIB}/export/files/system-pe.files`
	echo "\
$FILES \
./betarun/${BETARUN}/${CODEDIR}/betarun.lib \
./betarun/${BETARUN}/${CODEDIR}/betarunv.lib\
" \
| ${BETALIB}/export/misc/icomp $DST/system.cmd

echo "cd %BETALIB%\\betarun\\${BETARUN}\\${CODEDIR}"  > $DST/system-pe.cmd
echo "ren /Q betarun.lib  betarun.lib.orig"           >> $DST/system-pe.cmd
echo "ren /Q betarunv.lib betarunv.lib.orig"          >> $DST/system-pe.cmd
echo "copy /Q betarun.pe betarun.lib"                 >> $DST/system-pe.cmd
echo "copy /Q betarun.pe betarunv.lib"                >> $DST/system-pe.cmd
echo "copy /Q bin\\README.txt README.txt              >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
cat $DST/system.cmd                                   >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
echo "cd %BETALIB%\\betarun\\${BETARUN}\\${CODEDIR}"  >> $DST/system-pe.cmd
echo "del /Q betarun.lib"                             >> $DST/system-pe.cmd
echo "del /Q betarunv.lib"                            >> $DST/system-pe.cmd
echo "ren /Q betarunv.lib.orig betarunv.lib"          >> $DST/system-pe.cmd
echo "ren /Q betarun.lib.orig  betarun.lib"           >> $DST/system-pe.cmd
echo "cd %BETALIB%"                                   >> $DST/system-pe.cmd
mv $DST/system-pe.cmd  $DST/system.cmd

else
	
	echo ""
	echo "Creating $DST/system.tar "
	echo "(Listing in $DST/system.lst)"

	cd ${BETALIB}; 

	FILES=`${BETALIB}/export/files/system-pe.files`


	tar -covhf - $FILES \
	2> $DST/system.lst \
	 > $DST/system.tar

	if [ ! -d ${BETALIB}/test ]; then mkdir ${BETALIB}/test; fi
	cd ${BETALIB}/test
	echo "Adding betarun.pe as betarun.o and betarunv.o from directory"
	pwd

	/bin/rm -rf betarun
	mkdir betarun
	mkdir betarun/${BETARUN}
	mkdir betarun/${BETARUN}/$TARGET
	cp ${BETALIB}/betarun/${BETARUN}/$TARGET/betarun.pe ./betarun/${BETARUN}/$TARGET/betarun.o
	cp ${BETALIB}/betarun/${BETARUN}/$TARGET/betarun.pe ./betarun/${BETARUN}/$TARGET/betarunv.o

	tar -rovhf $DST/system.tar \
	  ./betarun/${BETARUN}/${CODEDIR}/betarun.o \
	  ./betarun/${BETARUN}/${CODEDIR}/betarunv.o  \
	>> $DST/system.lst

	echo "Compressing..."
	if [ -f $DST/system.tar.${ZEXT} ]
	then
	   /bin/rm -f $DST/system.tar.${ZEXT}
	fi
	$COMPRESS $DST/system.tar

fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack system
