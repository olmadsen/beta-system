cd external\libpng
make CC=gcc MACHINETYPE=nti_gnu lib.lib
cd ..\..\nti_gnu
ren libpng.a libpng.lib
