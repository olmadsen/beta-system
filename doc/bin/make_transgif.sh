#!/bin/sh

echo changing backgound color to transparent.

for f 
do
    echo $f
    giftrans -T $f >$f.trans
    mv $f.trans $f
done
