#!/bin/sh

rm -f elst
>log
for f in *.i SDK_IDL/*.i
do
  echo $f 
  echo $f >>log
  /users/olm/beta/bobs/parse /users/beta/r4.2/grammars/idl/idl-parser.btab $f  -ceol -case | tee -a log
done

  