#   File:       zlib.make
#   Target:     zlib
#   Created:    Friday, August 4, 2000 03:11:38 PM


MAKEFILE        = zlib.make
¥MondoBuild¥    = {MAKEFILE}  # Make blank to avoid rebuilds when makefile is modified

ObjDir          = :
Includes        = 

Sym-PPC         = -sym off

PPCCOptions     = {Includes} {Sym-PPC} 
ObjectDir		= :::ppcmac:

### Source Files ###

SrcFiles        =  ¶
				  adler32.c ¶
				  compress.c ¶
				  crc32.c ¶
				  gzio.c ¶
				  uncompr.c ¶
				  deflate.c ¶
				  trees.c ¶
				  zutil.c ¶
				  inflate.c ¶
				  infblock.c ¶
				  inftrees.c ¶
				  infcodes.c ¶
				  infutil.c ¶
				  inffast.c


### Object Files ###

ObjFiles-PPC    =  ¶
				  "{ObjDir}adler32.c.x" ¶
				  "{ObjDir}compress.c.x" ¶
				  "{ObjDir}crc32.c.x" ¶
				  "{ObjDir}gzio.c.x" ¶
				  "{ObjDir}uncompr.c.x" ¶
				  "{ObjDir}deflate.c.x" ¶
				  "{ObjDir}trees.c.x" ¶
				  "{ObjDir}zutil.c.x" ¶
				  "{ObjDir}inflate.c.x" ¶
				  "{ObjDir}infblock.c.x" ¶
				  "{ObjDir}inftrees.c.x" ¶
				  "{ObjDir}infcodes.c.x" ¶
				  "{ObjDir}infutil.c.x" ¶
				  "{ObjDir}inffast.c.x"


### Libraries ###

LibFiles-PPC    = 


### Default Rules ###

.c.x  Ä  .c  {¥MondoBuild¥}
	{PPCC} {depDir}{default}.c -o {targDir}{default}.c.x {PPCCOptions}


### Build Rules ###

zlib    ÄÄ  {ObjectDir}zlib.lib

{ObjectDir}zlib.lib  ÄÄ  {ObjFiles-PPC} {LibFiles-PPC} {¥MondoBuild¥}
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

"{ObjDir}adler32.c.x"  Ä  adler32.c
"{ObjDir}compress.c.x"  Ä  compress.c
"{ObjDir}crc32.c.x"  Ä  crc32.c
"{ObjDir}gzio.c.x"  Ä  gzio.c
"{ObjDir}uncompr.c.x"  Ä  uncompr.c
"{ObjDir}deflate.c.x"  Ä  deflate.c
"{ObjDir}trees.c.x"  Ä  trees.c
"{ObjDir}zutil.c.x"  Ä  zutil.c
"{ObjDir}inflate.c.x"  Ä  inflate.c
"{ObjDir}infblock.c.x"  Ä  infblock.c
"{ObjDir}inftrees.c.x"  Ä  inftrees.c
"{ObjDir}infcodes.c.x"  Ä  infcodes.c
"{ObjDir}infutil.c.x"  Ä  infutil.c
"{ObjDir}inffast.c.x"  Ä  inffast.c


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


