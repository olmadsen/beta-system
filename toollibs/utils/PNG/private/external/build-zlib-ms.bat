cd external\zlib
nmake /f msdos\makefile.w32 zlib.lib
del ..\..\nti_ms\zlib.lib 
move zlib.lib ..\..\nti_ms\
cd ..\..

