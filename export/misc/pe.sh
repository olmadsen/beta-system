#!/bin/sh

PACKSYSTEM=yes
PACKLIB=yes
PACKOBJECTSERVER=yes
PACKLIDSKJALV=yes

export PACKSYSTEM
export PACKLIB
export PACKLIDSKJALV
export PACKLIDSKJALV_XT
export PACKOBJECTSERVER


# === PERSONAL EDITION SYSTEM ===

DST=/users/beta/export/tarfiles/r3.1.1.pe
if [ ! -d $DST ]; then mkdir $DST; fi
DST=${DST}/${TARGET}
if [ ! -d $DST ]; then mkdir $DST; fi
export DST

echo Removing existing tar/lst/cmd files:
ls $DST/*
rm -f $DST/*

if [ "$PACKSYSTEM" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/system-pe.sh
fi

if [ "$PACKLIB" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/lib-pe.sh
fi

if [ "$PACKXT" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/xt.sh
fi

if [ "$PACKLIDSKJALV" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/lidskjalv.sh
fi

if [ "$PACKCONTRIB" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/contrib.sh
fi

if [ "$TARGET" = "nti" ]
then
   /users/beta/export/distribution/r3.1.1/misc/make_list.perl $DST/*.cmd
else
   /users/beta/export/distribution/r3.1.1/misc/make_list.perl $DST/*.lst
fi
