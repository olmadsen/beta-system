#   File:       libpng.make
#   Target:     libpng
#   Created:    Friday, August 4, 2000 03:22:05 PM


MAKEFILE        = libpng.make
¥MondoBuild¥    = {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified

ObjDir          = :
Includes        = -I ::zlib

Sym-PPC         = -sym off

PPCCOptions     = {Includes} {Sym-PPC} -D MACOS
ObjectDir		= :::ppcmac:



### Source Files ###

SrcFiles        =  ¶
				  png.c ¶
				  pngset.c ¶
				  pngget.c ¶
				  pngrutil.c ¶
				  pngtrans.c ¶
				  pngwutil.c ¶
				  pngread.c ¶
				  pngrio.c ¶
				  pngwio.c ¶
				  pngwrite.c ¶
				  pngrtran.c ¶
				  pngwtran.c ¶
				  pngmem.c ¶
				  pngerror.c ¶
				  pngpread.c


### Object Files ###

ObjFiles-PPC    =  ¶
				  "{ObjDir}png.c.x" ¶
				  "{ObjDir}pngset.c.x" ¶
				  "{ObjDir}pngget.c.x" ¶
				  "{ObjDir}pngrutil.c.x" ¶
				  "{ObjDir}pngtrans.c.x" ¶
				  "{ObjDir}pngwutil.c.x" ¶
				  "{ObjDir}pngread.c.x" ¶
				  "{ObjDir}pngrio.c.x" ¶
				  "{ObjDir}pngwio.c.x" ¶
				  "{ObjDir}pngwrite.c.x" ¶
				  "{ObjDir}pngrtran.c.x" ¶
				  "{ObjDir}pngwtran.c.x" ¶
				  "{ObjDir}pngmem.c.x" ¶
				  "{ObjDir}pngerror.c.x" ¶
				  "{ObjDir}pngpread.c.x"


### Libraries ###

LibFiles-PPC    = 


### Default Rules ###

.c.x  Ä  .c  {¥MondoBuild¥}
	{PPCC} {depDir}{default}.c -o {targDir}{default}.c.x {PPCCOptions}


### Build Rules ###

libpng    ÄÄ  {ObjectDir}libpng.lib

{ObjectDir}libpng.lib ÄÄ  {ObjFiles-PPC} {LibFiles-PPC} {¥MondoBuild¥}
	PPCLink ¶
		-o {Targ} ¶
		{ObjFiles-PPC} ¶
		{LibFiles-PPC} ¶
		{Sym-PPC} ¶
		-mf -d ¶
		-t 'XCOF' ¶
		-c 'MPS ' ¶
		-xm l



### Required Dependencies ###

"{ObjDir}png.c.x"  Ä  png.c
"{ObjDir}pngset.c.x"  Ä  pngset.c
"{ObjDir}pngget.c.x"  Ä  pngget.c
"{ObjDir}pngrutil.c.x"  Ä  pngrutil.c
"{ObjDir}pngtrans.c.x"  Ä  pngtrans.c
"{ObjDir}pngwutil.c.x"  Ä  pngwutil.c
"{ObjDir}pngread.c.x"  Ä  pngread.c
"{ObjDir}pngrio.c.x"  Ä  pngrio.c
"{ObjDir}pngwio.c.x"  Ä  pngwio.c
"{ObjDir}pngwrite.c.x"  Ä  pngwrite.c
"{ObjDir}pngrtran.c.x"  Ä  pngrtran.c
"{ObjDir}pngwtran.c.x"  Ä  pngwtran.c
"{ObjDir}pngmem.c.x"  Ä  pngmem.c
"{ObjDir}pngerror.c.x"  Ä  pngerror.c
"{ObjDir}pngpread.c.x"  Ä  pngpread.c


### Optional Dependencies ###
### Build this target to generate "include file" dependencies. ###

Dependencies  Ä  $OutOfDate
	MakeDepend ¶
		-append {MAKEFILE} ¶
		-ignore "{CIncludes}" ¶
		-objdir "{ObjDir}" ¶
		-objext .x ¶
		{Includes} ¶
		{SrcFiles}


