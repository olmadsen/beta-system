#!/bin/sh

export CC=gcc

mkdir -p $BETALIB/lib/nti_gnu

cd zlib
gmake
cp ../../libz.a $BETALIB/lib/nti_gnu


cd ../libpng
gmake
cp ../../libpng.a $BETALIB/lib/nti_gnu

cd ..
