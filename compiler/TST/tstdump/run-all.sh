#!/bin/sh

. $BETALIB/configuration/env.sh

BETART="";
export BETART

LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:../lib/${objdir}"
export LD_LIBRARY_PATH

echo ""
echo Removing old output- and dump files...
echo "======================================================"
/bin/rm -f *.out
/bin/rm -f *.dump

echo ""
echo Compiling all...
echo "======================================================"
beta -qw tstdump??.bet

echo ""
echo Running all...
echo "======================================================"
for f in tstdump??
do
    echo ""
    echo "--------" $f: "-------"
    if [ $f = "tstdump24" ]; then
       echo $f skipped.
       echo "--------------------------"
       continue
    fi 
    if [ $f = "tstdump26" ]; then
       echo $f will attempt to provoke stack overflow.
       echo This is not handled correctly by betarun. tstdump26 skipped.
       #echo This will take a while, and will probably not be.
       #echo caught properly be betarun, but instead dump core.
       #$f
       #/bin/rm -f core
       #echo "--------------------------"
       continue
    fi 
    $f >$f.out 2>&1
    if [ -f output/$f.out ]; then
       diff output/$f.out $f.out
       if [ $? = 0 ]; then
	  echo "[Output is correct]"
	  rm $f.out
       else
	  echo "[Difference in output]"
       fi
    else
       echo "[No reference output exists]"
    fi
    echo "--------------------------"
done

echo ""
echo "Diffing all (left is correct version)..."
echo "======================================================"
for f in tstdump??.dump
do
    echo ""
    echo "--------" $f: "-------"
    if [ -f dumps/$f ]; then
       sed -e "s/$objdir/MACHINE_TYPE/g" < $f | diff dumps/$f -
       if [ $? = 0 ]; then
	  echo "[Dump is correct]"
	  rm $f
       else
	  echo "[Difference in dump]"
       fi
    else
       echo "[No reference dump exists]"
    fi
    echo "--------------------------------"
done

echo ""
echo "======================================================"
echo Done.

