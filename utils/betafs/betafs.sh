#!/bin/sh

BETALIB=${BETALIB-/usr/local/lib/beta}
export BETALIB   # needed if pathhandler is used
. $BETALIB/configuration/r4.0/env.sh
LOCATION=$BETALIB/utils/betafs/v1.1/$objdir/

if [ "$MACHINETYPE" = "SGI" ]
then
  LD_LIBRARY_PATH=$LOCATION:${LD_LIBRARY_PATH}
  export LD_LIBRARY_PATH
fi

$LOCATION/betafs "$@"

