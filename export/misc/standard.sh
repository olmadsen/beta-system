#!/bin/sh 

# === STANDARD SYSTEM ===

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

echo Removing existing tar/lst files:
ls $DST/*
rm -f $DST/*

if [ "$PACKSYSTEM" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/system.sh
fi

if [ "$PACKLIB" = "yes" ]; then
   PACKOBJECTSERVER=yes
   export PACKOBJECTSERVER
   /users/beta/export/distribution/r4.0.1/misc/lib.sh
   PACKOBJECTSERVER=packed
   export PACKOBJECTSERVER
fi

if [ "$PACKYGGDRASIL" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/yggdrasil.sh
fi

if [ "$PACKEDITOR" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/editor.sh
fi
if [ "$PACKEDITOR5_0" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/editor5_0.sh
fi

if [ "$PACKXT" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/xt.sh
fi

if [ "$PACKBIFROST" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/bifrost.sh
fi

if [ "$PACKVALHALLA" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/valhalla.sh
fi
if [ "$PACKVALHALLA2_0" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/valhalla2_0.sh
fi

if [ "$PACKFREJA" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/freja.sh
fi

if [ "$PACKYMER" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/ymer.sh
fi

if [ "$PACKFRIGG" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/frigg.sh
fi

if [ "$PACKLIDSKJALV" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/lidskjalv.sh
fi

if [ "$PACKOODB" = "yes" ]; then
   if [ "$PACKOBJECTSERVER" != "packed" ];
   then
     PACKOBJECTSERVER=yes
     export PACKOBJECTSERVER
   fi
   PACKDISTRIBUTION=yes
   export PACKDISTRIBUTION
   /users/beta/export/distribution/r4.0.1/misc/oodb.sh
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
   /users/beta/export/distribution/r4.0.1/misc/distribution.sh
   PACKOBJECTSERVER=packed
   export PACKOBJECTSERVER
fi

if [ "$PACKOBJECTSERVER" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/objectserver.sh
fi

if [ "$PACKGDMO" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/gdmo.sh
fi

if [ "$PACKCONTRIB" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/contrib.sh
fi

if [ "$PACKBETACL" = "yes" ]; then
   /users/beta/export/distribution/r4.0.1/misc/betacl.sh
fi

if [ "$TARGET" = "nti" ]
then
   /users/beta/export/distribution/r4.0.1/misc/make_list.perl $DST/*.cmd
else
   /users/beta/export/distribution/r4.0.1/misc/make_list.perl $DST/*.lst
fi