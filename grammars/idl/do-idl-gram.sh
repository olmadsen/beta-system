#/bin/sh

generator idl
mv idl-parser.bobs idl-parser.generated
echo Fixing '<<' in idl-parser.bobs
head -3 idl-parser.generated | sed -e 's/"\<\<"/"\!\!"/'  >idl-parser.bobs
tail +4 idl-parser.generated                             >>idl-parser.bobs
dogram idl
