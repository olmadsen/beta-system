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
	echo '  echo "mac.pack Disk:beta:"'                           >>$DST/mac.pack
	echo '  exit 4;'                                              >>$DST/mac.pack
	echo 'End'                                                    >>$DST/mac.pack
	echo 'echo mac.pack: Installing into {newBeta}'               >>$DST/mac.pack
	echo 'newfolder {newBeta} „ Dev:Null'                      >>$DST/mac.pack

	echo ""
	echo "Creating $DST/system.pack"
        echo "echo 'Doing system ...'" >>$DST/mac.pack
        echo "system.pack"           >>$DST/mac.pack
	FILES=`${BETALIB}/export/files/system.files`
	echo "$FILES" | ${BETALIB}/export/misc/maccomp $DST/system.pack

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
fi

. ${BETALIB}/export/misc/check_problems.sh
check_pack system