#!/bin/sh

# Any 16 bit integer as key for REAL-betarun;  Just don't forget the key!!
PRODKEY=39746

if [ -z "$TARGET" ]; then echo "TARGET not set"; exit 1 ;fi
MACHINE=`echo "$TARGET" | tr "[a-z]" "[A-Z]"`
export MACHINE

if [ -z "$DST" ]; then echo "DST not set"; exit 1 ;fi
if [ -z "$AST" ]; then echo "AST not set"; exit 1 ;fi
if [ -z "$ZEXT" ]; then echo "ZEXT not set"; exit 1 ;fi
if [ -z "$COMPRESS" ]; then echo "COMPRESS not set"; exit 1 ;fi


if [ "$COMPRESS" = "icomp" ]
then
	########################### WINDOWS ###########################
	echo ""
	echo "Creating $DST/system.cmd"
	FILES=`${BETALIB}/export/files/system-pe.files`
	echo "\
$FILES \
./betarun/${CODEDIR}/betarun.lib \
./betarun/${CODEDIR}/betarun_v.lib \
" \
| ${BETALIB}/export/misc/icomp $DST/system.cmd

# ./betarun/${CODEDIR}/betarun_lib.crypt \
# ./betarun/${CODEDIR}/betarun_v_lib.crypt \
# ./betarun/${CODEDIR}/decrypt.exe \

echo "system0"                                       > $DST/system-pe.cmd
#echo "cd %BETALIB%\\betarun\\${CODEDIR}"            >> $DST/system-pe.cmd
#echo "ren  betarun.lib  betarun.lib.orig"           >> $DST/system-pe.cmd
#echo "ren  betarun_v.lib betarun_v.lib.orig"        >> $DST/system-pe.cmd
#echo "copy  betarun_pe.lib betarun.lib"             >> $DST/system-pe.cmd
#echo "copy  betarun_pe.lib betarun_v.lib"           >> $DST/system-pe.cmd
#echo "copy  %BETALIB%\\crypt\\nti\\decrypt.exe" >> $DST/system-pe.cmd
#echo "%BETALIB%\\crypt\\nti\\encrypt.exe $PRODKEY 0 betarun.lib.orig betarun_lib.crypt" >> $DST/system-pe.cmd
#echo "%BETALIB%\\crypt\\nti\\encrypt.exe $PRODKEY 0 betarun_v.lib.orig betarun_v_lib.crypt" >> $DST/system-pe.cmd
echo "cd %BETALIB%"                                 >> $DST/system-pe.cmd
echo "copy  bin\\README.txt README.txt"             >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
cat $DST/system0.cmd                                >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
#echo "cd %BETALIB%\\betarun\\${CODEDIR}"           >> $DST/system-pe.cmd
#echo "del  betarun.lib"                             >> $DST/system-pe.cmd
#echo "del  betarun_v.lib"                           >> $DST/system-pe.cmd
#echo "del  betarun*.crypt"                          >> $DST/system-pe.cmd
#echo "del  decrypt.exe"                             >> $DST/system-pe.cmd
#echo "ren  betarun_v.lib.orig betarun_v.lib"        >> $DST/system-pe.cmd
#echo "ren  betarun.lib.orig  betarun.lib"           >> $DST/system-pe.cmd
#echo "cd %BETALIB%"                                   >> $DST/system-pe.cmd
mv $DST/system-pe.cmd  $DST/system0.cmd

else
if [ "$COMPRESS" = "maccomp" ]
then
	###################### MACINTOSH #########################
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
echo "newfolder {newbeta}betarun:ppcmac: „ Dev:Null"  >> $DST/system.pack

# add special betarun files
echo "duplicate {betalib}betarun:${CODEDIR}:betarun.obj {newbeta}betarun:${CODEDIR}:betarun.obj"  \
  >> $DST/system.pack
echo "duplicate {betalib}betarun:${CODEDIR}:betarun_v.obj {newbeta}betarun:${CODEDIR}:betarun_v.obj" \
  >> $DST/system.pack

# Encryption and copying of REAL-betarun:
# FIXME!! Is this correct/possible on mac? --grouleff
#echo "{betalib}crypt:ppcmac:encrypt $PRODKEY 0 {betalib}betarun:${CODEDIR}:betarun.obj {newbeta}betarun:${CODEDIR}:betarun_obj.crypt" >> $DST/system.pack
#echo "{betalib}crypt:ppcmac:encrypt $PRODKEY 0 {betalib}betarun:${CODEDIR}:betarun_v.obj {newbeta}betarun:${CODEDIR}:betarun_obj_v.crypt" >> $DST/system.pack

# Add locking of betarun files if specified in environment.
if [ "$BETALOCK" = "yes" ]
then
# DO NOT lock betarun, as that makes decrypting for prof version difficult.
#  echo "setfile -a L {newbeta}betarun:${CODEDIR}:betarun‰" \
  >> $DST/system.pack
fi

else	
	##################### UNIX ######################
	if [ "$TARGET" = "sun4s" ]; then
	    BETARUN_EXT="a"
	else
	    BETARUN_EXT="o"
	fi
	echo ""
	echo "Creating $DST/system.tar "
	echo "(Listing in $DST/system.lst)"

	cd ${BETALIB}; 

	FILES=`${BETALIB}/export/files/system-pe.files`


	tar -covhf - $FILES \
	2> $DST/system.lst \
	 > $DST/system.tar

	if [ ! -d ${BETALIB}/test ]; then mkdir ${BETALIB}/test; fi
	#cd ${BETALIB}/test
	#echo "Adding betarun_pe.${BETARUN_EXT} as betarun.${BETARUN_EXT} and betarun_v.${BETARUN_EXT} from directory"
	#pwd

	/bin/rm -rf betarun
	mkdir betarun
	mkdir betarun/$TARGET
	cp ${BETALIB}/betarun/$TARGET/betarun.${BETARUN_EXT} ./betarun/$TARGET/betarun.${BETARUN_EXT}
	cp ${BETALIB}/betarun/$TARGET/betarun_v.${BETARUN_EXT} ./betarun/$TARGET/betarun_v.${BETARUN_EXT}
#	cp ${BETALIB}/crypt/${TARGET}/decrypt ./betarun/$TARGET/
#	${BETALIB}/crypt/${objdir}/encrypt $PRODKEY 0 ${BETALIB}/betarun/$TARGET/betarun.${BETARUN_EXT} ./betarun/$TARGET/betarun_o.crypt
#	${BETALIB}/crypt/${objdir}/encrypt $PRODKEY 0 ${BETALIB}/betarun/$TARGET/betarun_v.${BETARUN_EXT} ./betarun/$TARGET/betarun_v_o.crypt
	tar -rovhf $DST/system.tar \
	  ./betarun/${CODEDIR}/betarun.${BETARUN_EXT} \
	  ./betarun/${CODEDIR}/betarun_v.${BETARUN_EXT}  \
	>> $DST/system.lst

#	  ./betarun/${CODEDIR}/betarun_o.crypt  \
#	  ./betarun/${CODEDIR}/betarun_v_o.crypt  \
#	  ./betarun/${CODEDIR}/decrypt  \

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
