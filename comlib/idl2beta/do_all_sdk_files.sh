#!/bin/sh

>log
for f in [ test/SDK_IDL/*.idl test/SDK_IDL/*.Idl ]
do
  echo $f 
  echo $f >> log
  bidl -f -q -e $f | tee -a log
done

  