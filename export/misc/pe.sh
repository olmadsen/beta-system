#!/bin/sh 

# === PE SYSTEM ===

# if not specified above: default to "no"

PACKSYSTEM=${PACKSYSTEM-"no"}
PACKLIB=${PACKLIB-"no"}
PACKYGGDRASIL=${PACKYGGDRASIL-"no"}
PACKEDITOR=${PACKEDITOR-"no"}
PACKFRIGG=${PACKFRIGG-"no"}
PACKYMER=${PACKYMER-"no"}
PACKXT=${PACKXT-"no"}
PACKBIFROST=${PACKBIFROST-"no"}
PACKVALHALLA=${PACKVALHALLA-"no"}
PACKFREJA=${PACKFREJA-"no"}
PACKLIDSKJALV=${PACKLIDSKJALV-"no"}
PACKOODB=${PACKOODB-"no"}
PACKGDMO=${PACKGDMO-"no"}
PACKPERSISTENCE=${PACKPERSISTENCE-"no"}
PACKOBJECTSERVER=${PACKOBJECTSERVER-"no"}

export PACKLIB
export PACKPERSISTENCE
export PACKOBJECTSERVER
export PACKSYSTEM
export PACKVALHALLA
export PACKYGGDRASIL
export PACKEDITOR
export PACKFRIGG
export PACKYMER
export PACKXT
export PACKBIFROST
export PACKFREJA
export PACKLIDSKJALV
export PACKOODB
export PACKGDMO
export PACKCONTRIB

DST=${BETALIB}/export/tarfiles
if [ ! -d $DST ]; then mkdir $DST; fi
DST=${DST}/${TARGET}.pe
if [ ! -d $DST ]; then mkdir $DST; fi
export DST

echo Removing existing tar/lst files:
ls $DST/*
rm -f $DST/*

if [ "$PACKSYSTEM" = "yes" ]; then
   ${BETALIB}/export/misc/system-pe.sh
fi

if [ "$PACKLIB" = "yes" ]; then
   PACKOBJECTSERVER=yes
   export PACKOBJECTSERVER
   ${BETALIB}/export/misc/lib.sh
   PACKOBJECTSERVER=packed
   export PACKOBJECTSERVER
fi

if [ "$PACKYGGDRASIL" = "yes" ]; then
   ${BETALIB}/export/misc/yggdrasil.sh
fi

if [ "$PACKEDITOR" = "yes" ]; then
   ${BETALIB}/export/misc/editor.sh
fi
if [ "$PACKEDITOR5_0" = "yes" ]; then
   ${BETALIB}/export/misc/editor5_0.sh
fi

if [ "$PACKXT" = "yes" ]; then
   ${BETALIB}/export/misc/xt.sh
fi

if [ "$PACKBIFROST" = "yes" ]; then
   ${BETALIB}/export/misc/bifrost.sh
fi

if [ "$PACKVALHALLA" = "yes" ]; then
   ${BETALIB}/export/misc/valhalla.sh
fi
if [ "$PACKVALHALLA2_0" = "yes" ]; then
   ${BETALIB}/export/misc/valhalla2_0.sh
fi

if [ "$PACKFREJA" = "yes" ]; then
   ${BETALIB}/export/misc/freja.sh
fi

if [ "$PACKYMER" = "yes" ]; then
   ${BETALIB}/export/misc/ymer.sh
fi

if [ "$PACKFRIGG" = "yes" ]; then
   ${BETALIB}/export/misc/frigg.sh
fi

if [ "$PACKLIDSKJALV" = "yes" ]; then
   ${BETALIB}/export/misc/lidskjalv.sh
fi

if [ "$PACKOODB" = "yes" ]; then
   if [ "$PACKOBJECTSERVER" != "packed" ];
   then
     PACKOBJECTSERVER=yes
     export PACKOBJECTSERVER
   fi
   PACKDISTRIBUTION=yes
   export PACKDISTRIBUTION
   ${BETALIB}/export/misc/oodb.sh
   PACKOBJECTSERVER=packed
   export PACKOBJECTSERVER
   PACKDISTRIBUTION=packed
   export PACKDISTRIBUTION
fi

if [ "$PACKDISTRIBUTION" = "yes" ]; then
   if [ "$PACKOBJECTSERVER" != "packed" ];
   then
     PACKOBJECTSERVER=yes
     export PACKOBJECTSERVER
   fi
   ${BETALIB}/export/misc/distribution.sh
   PACKOBJECTSERVER=packed
   export PACKOBJECTSERVER
fi

if [ "$PACKOBJECTSERVER" = "yes" ]; then
   ${BETALIB}/export/misc/objectserver.sh
fi

if [ "$PACKGDMO" = "yes" ]; then
   ${BETALIB}/export/misc/gdmo.sh
fi

if [ "$PACKCONTRIB" = "yes" ]; then
   ${BETALIB}/export/misc/contrib.sh
fi

if [ "$PACKBETACL" = "yes" ]; then
   ${BETALIB}/export/misc/betacl.sh
fi

if [ "$TARGET" = "nti" ]
then
   ${BETALIB}/export/misc/make_list.perl $DST/*.cmd
else
   ${BETALIB}/export/misc/make_list.perl $DST/*.lst
fi

if [ -f $DST/errors.lst ]
then
  echo List of errors in file $DST/errors.lst
fi
