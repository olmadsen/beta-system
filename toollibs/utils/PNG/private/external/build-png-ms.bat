cd external\libpng
nmake /f scripts\makefile.w32
del  ..\..\nti_ms\libpng.lib
move libpng.lib ..\..\nti_ms\
cd ..\..
