#!/bin/sh

# This script is 'dotted' by */interface/makeHTML scripts
# and implements generic generation of HTML files from BETA files.

# Must be set:
#  BETALIB  used to find source files
#  SRC      base directory for interface files
#  FILES    .bet files to include (releative to $SRC)
#  MAKEINT  beta2int.perl command, including relative path
#  MAKEHTML int2html.perl command, including relative path
# Can be set:
#  INTPOST  Postprocessor applied after $MAKEINT, before $MAKEHTML
#  OPTIONS  Extra options for $MAKEHTML 
#  QUIET    Be quiet

if [ "$BETALILB" = "" ]; then echo "$0: no BETALIB directory specified"; exit 1; fi
if [ "$SRC"      = "" ]; then echo "$0: no SRC directory specified"; exit 1; fi
if [ "$FILES"    = "" ]; then echo "$0: no FILES list specified"; exit 1; fi
if [ "$MAKEINT"  = "" ]; then echo "$0: no MAKEINT script specified"; exit 1; fi
if [ "$MAKEHTML" = "" ]; then echo "$0: no MAKEHTML script specified"; exit 1; fi

/bin/rm -f *.int

if [ "$QUIET" != "1" ]; then
    echo Making interface descriptions for \"$SRC\" ...
    echo ""
fi
for srcdir in $SRC
do
    for file in $FILES
    do
	if [ ! -f $srcdir/$file ]; then continue; fi
	INT=`basename $srcdir/$file .bet`.int
	if [ "$QUIET" != "1" ]; then
	    echo Making $INT from $srcdir/$file ...
	fi
	if [ -n "$INTPOST" ]; then
	   if [ "$QUIET" != "1" ]; then
		echo Performing $INTPOST before $MAKEHTML
	   fi
	   expand $srcdir/$file | $MAKEINT | $INTPOST > $INT
	else
	   expand $srcdir/$file | $MAKEINT > $INT
	fi
	INTFILES="${INTFILES} $INT"
    done
done

if [ "$QUIET" != "1" ]; then
    echo Creating HTML:
    OPTIONS="$OPTIONS -v"
fi
$MAKEHTML $OPTIONS $INTFILES
/bin/rm -f *.int
if [ "$QUIET" != "1" ]; then
    echo done.
fi