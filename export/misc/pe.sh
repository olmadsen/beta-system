#!/bin/sh

export PACKSYSTEM
export PACKLIB
export PACKXT
export PACKLIDSKJALV
export PACKOBJECTSERVER


# === STANDARD SYSTEM ===


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
   /users/beta/export/distribution/r3.1.1/misc/xt-pe.sh
fi

if [ "$PACKCONTRIB" = "yes" ]; then
   /users/beta/export/distribution/r3.1.1/misc/contrib.sh
fi

/users/beta/export/distribution/r3.1.1/misc/check_problems.sh