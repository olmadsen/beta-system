mkdir /s ..\..\..\..\..\..\lib\nti

chdir zlib
nmake /f msdos\makefile.w32
move zlib.lib ..\..\..\..\..\..\lib\nti\zlib.lib


chdir ..\libpng
nmake /f scripts\makefile.w32
move libpng.lib ..\..\..\..\..\..\lib\nti\zlib.lib

chdir ..

