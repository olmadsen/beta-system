#!/bin/sh

echo ""
echo removing old dump files...
/bin/rm -f *.dump

echo ""
echo compiling all...
beta -qw tstdump??.bet

echo ""
echo running all...
for f in tstdump??
do
    echo ""
    echo "--------" $f "-------":
    if [ $f = "tstdump24" ]; then
       echo $f skipped.
       echo "--------------------------"
       continue
    fi 
    if [ $f = "tstdump26" ]; then
       echo $f will attempt to provoke stack overflow.
       echo This will take a while, and will probably not be.
       echo caught properly be betarun, but instead dump core.
       $f
       /bin/rm -f core
       echo "--------------------------"
       continue
    fi 
    $f
    echo "--------------------------"
done

echo ""
echo done.

