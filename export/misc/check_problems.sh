#!/bin/sh

check_pack()
{
	if [ "$COMPRESS" = "icomp" ]
	then
		exit 0
	fi

	echo Checking $1...
	pack=$1
	cd $DST
	PROBLEMS=`grep -v '^a' $pack.lst`
	STRANGE=`egrep -e '~|^#|core|\.dump' $pack.lst`
	if [ "$STRANGE" != "" ]
	then
		echo "" | tee -a $DST/errors.lst
		echo "*** STRANGE FILES PACKED (consult $DST/$pack.lst):" \
                        | tee -a $DST/errors.lst
		echo "" | tee -a $DST/errors.lst
		egrep -e '~|^#|core|\.dump' $pack.lst | tee -a $DST/errors.lst
	fi
	if [ "$PROBLEMS" != "" ]
	then
		echo "" | tee -a $DST/errors.lst
		echo "*** PROBLEMS (consult $DST/$pack.lst):" \
                        | tee -a $DST/errors.lst
		echo "" | tee -a $DST/errors.lst
		#echo $PROBLEMS | tee -a $DST/errors.lst
		grep -v '^a' $pack.lst | tee -a $DST/errors.lst
	fi

}
