mkdir /s %betalib%\lib\nti

chdir zlib
nmake /f msdos\makefile.w32
move zlib.lib %betalib%\lib\nti\


chdir ..\libpng
nmake /f scripts\makefile.w32
move libpng.lib %betalib%\lib\nti\

chdir ..

