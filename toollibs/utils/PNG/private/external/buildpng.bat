mkdir /s %betalib%\lib\nti_ms

chdir zlib
nmake /f msdos\makefile.w32
move zlib.lib %betalib%\lib\nti_ms\


chdir ..\libpng
nmake /f scripts\makefile.w32
move libpng.lib %betalib%\lib\nti_ms\

chdir ..

