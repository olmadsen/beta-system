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
	########################### WINDOWS ###########################
	echo ""
	echo "Creating $DST/system.cmd"
	FILES=`${BETALIB}/export/files/system-pe.files`
	echo "\
$FILES \
" \
| ${BETALIB}/export/misc/icomp $DST/system.cmd

echo "system0"                                       > $DST/system-pe.cmd
echo "cd %BETALIB%"                                 >> $DST/system-pe.cmd
echo "copy  bin\\README.txt README.txt"             >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
cat $DST/system0.cmd                                >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
echo ""                                             >> $DST/system-pe.cmd
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


else	
	##################### UNIX ######################
	echo ""
	echo "Creating $DST/system.tar "
	echo "(Listing in $DST/system.lst)"

	cd ${BETALIB}; 

	FILES=`${BETALIB}/export/files/system-pe.files`

	tar -covhf - $FILES \
	2> $DST/system.lst \
	 | $COMPRESS >  $DST/system.tar.${ZEXT}
fi
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack system
