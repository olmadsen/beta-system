#!/bin/sh

# This script is 'dotted' by */interface/makeHTML scripts
# and implements generic generation of HTML files from BETA files.

# Must be set:
#  SRC      base directory for interface files
#  FILES    .bet files to include (releative to $SRC)
#  MAKEINT  beta2int.perl command, including relative path
#  MAKEHTML int2html.perl command, including relative path
# Can be set:
#  INTPOST  Postprocessor applied after $MAKEINT, before $MAKEHTML
#  OPTIONS  Extra options for $MAKEHTML 

/bin/rm -f *.int
echo Making interface descriptions for $SRC.
echo ""
for srcdir in $SRC
do
    for file in $FILES
    do
	if [ ! -f $srcdir/$file ]; then continue; fi
	INT=`basename $srcdir/$file .bet`.int
	echo Making $INT from $srcdir/$file ...
	if [ -n "$INTPOST" ]; then
	   echo Performing $INTPOST before $MAKEHTML
	   expand $srcdir/$file | $MAKEINT | $INTPOST > $INT
	else
	   expand $srcdir/$file | $MAKEINT > $INT
	fi
	INTFILES="${INTFILES} $INT"
    done
done

echo Creating HTML:
$MAKEHTML $OPTIONS $INTFILES
/bin/rm -f *.int
echo done.

