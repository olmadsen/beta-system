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
./betarun/${BETARUN}/${CODEDIR}/betarun_v.lib\
" \
| ${BETALIB}/export/misc/icomp $DST/system.cmd

echo "cd %BETALIB%\\betarun\\${BETARUN}\\${CODEDIR}"  > $DST/system-pe.cmd
echo "ren /Q betarun.lib  betarun.lib.orig"           >> $DST/system-pe.cmd
echo "ren /Q betarun_v.lib betarun_v.lib.orig"        >> $DST/system-pe.cmd
echo "copy /Q betarun_pe.lib betarun.lib"             >> $DST/system-pe.cmd
echo "copy /Q betarun_pe.lib betarun_v.lib"           >> $DST/system-pe.cmd
echo "copy /Q bin\\README.txt README.txt"             >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
cat $DST/system.cmd                                   >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
echo ""                                               >> $DST/system-pe.cmd
echo "cd %BETALIB%\\betarun\\${BETARUN}\\${CODEDIR}"  >> $DST/system-pe.cmd
echo "del /Q betarun.lib"                             >> $DST/system-pe.cmd
echo "del /Q betarun_v.lib"                           >> $DST/system-pe.cmd
echo "ren /Q betarun_v.lib.orig betarun_v.lib"        >> $DST/system-pe.cmd
echo "ren /Q betarun.lib.orig  betarun.lib"           >> $DST/system-pe.cmd
echo "cd %BETALIB%"                                   >> $DST/system-pe.cmd
mv $DST/system-pe.cmd  $DST/system.cmd

else
if [ "$COMPRESS" = "maccomp" ]
then

	echo ""
	echo "Creating $DST/mac.pack"
	echo '# Usage:    makeExport MyDisk:beta:'                    > $DST/mac.pack
	echo 'if {#} == 0'                                            >>$DST/mac.pack
	echo 'else'                                                   >>$DST/mac.pack
	echo '    Set newBeta {1}         # The directory to copy to' >>$DST/mac.pack
	echo '    export newBeta'                                     >>$DST/mac.pack
	echo 'End'                                                    >>$DST/mac.pack
	echo 'IF {newBeta} == ""'                                     >>$DST/mac.pack
	echo '  echo "# Usage - {0} folder" > Dev:StdErr'             >>$DST/mac.pack
	echo '  echo "# "'                                            >>$DST/mac.pack
	echo '  echo "mac.pack  Disk:beta:"'                          >>$DST/mac.pack
	echo '  exit 4;'                                              >>$DST/mac.pack
	echo 'End'                                                    >>$DST/mac.pack
	echo 'echo mac.pack: Installing into {newBeta}'               >>$DST/mac.pack
	echo 'newfolder {newBeta} „ Dev:Null'                      >>$DST/mac.pack

	echo ""
	echo "Creating $DST/system.pack"
        echo "echo 'Doing system ...'" >>$DST/mac.pack
        echo "system.pack"           >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/system-pe.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/system.pack

echo ""                                                       >> $DST/system.pack
echo "# special PE betarun"                                   >> $DST/system.pack
echo "newfolder {newbeta}betarun: „ Dev:Null"              >> $DST/system.pack
echo "newfolder {newbeta}betarun:v2.9: „ Dev:Null"         >> $DST/system.pack
echo "newfolder {newbeta}betarun:v2.9:ppcmac: „ Dev:Null"  >> $DST/system.pack

# add special betarun files
echo "duplicate {betalib}betarun:${BETARUN}:${CODEDIR}:betarun_pe.obj {newbeta}betarun:${BETARUN}:${CODEDIR}:betarun.obj"  \
  >> $DST/system.pack
echo "duplicate {betalib}betarun:${BETARUN}:${CODEDIR}:betarun_pe.obj {newbeta}betarun:${BETARUN}:${CODEDIR}:betarun_v.obj" \
  >> $DST/system.pack

# Add locking of betarun files if specified in environment.
if [ "$BETALOCK" = "yes" ]
then
  echo "setfile -a L {newbeta}betarun:${BETARUN}:${CODEDIR}:betarun‰" \
  >> $DST/system.pack
fi

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
	echo "Adding betarun_pe.o as betarun.o and betarun_v.o from directory"
	pwd

	/bin/rm -rf betarun
	mkdir betarun
	mkdir betarun/${BETARUN}
	mkdir betarun/${BETARUN}/$TARGET
	cp ${BETALIB}/betarun/${BETARUN}/$TARGET/betarun_pe.o ./betarun/${BETARUN}/$TARGET/betarun.o
	cp ${BETALIB}/betarun/${BETARUN}/$TARGET/betarun_pe.o ./betarun/${BETARUN}/$TARGET/betarun_v.o

	tar -rovhf $DST/system.tar \
	  ./betarun/${BETARUN}/${CODEDIR}/betarun.o \
	  ./betarun/${BETARUN}/${CODEDIR}/betarun_v.o  \
	>> $DST/system.lst

	/bin/rm -rf betarun
	
	echo "Compressing..."
	if [ -f $DST/system.tar.${ZEXT} ]
	then
	   /bin/rm -f $DST/system.tar.${ZEXT}
	fi
	$COMPRESS $DST/system.tar

fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack system
