!#/bin/sh

for name in *.xpm
do
echo $name
convert $name `basename $name .xpm`.png
done
