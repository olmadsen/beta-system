#!/bin/sh

>log
for f in *.idl *.Idl SDK_IDL/*.idl SDK_IDL/*.Idl
do
  echo $f 
  echo $f >>log
  ../bidl -f -q -p $f | tee -a log
done

  