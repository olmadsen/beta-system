#!/bin/sh

check_pack()
{
	echo Checking $1...
	pack=$1
	cd $DST
	PROBLEMS=`grep -v '^a' $pack.lst`
	STRANGE=`egrep -e '~|^#|core|\.dump' $pack.lst`
	if [ "$STRANGE" != "" ]
	then
		echo ""
		echo "*** STRANGE FILES PACKED (consult $DST/$pack.lst):"
		echo ""
		egrep -e '~|^#|core|\.dump' $pack.lst
	fi
	if [ "$PROBLEMS" != "" ]
	then
		echo ""
		echo "*** PROBLEMS (consult $DST/$pack.lst):"
		echo ""
		#echo $PROBLEMS
		grep -v '^a' $pack.lst
	fi

}
