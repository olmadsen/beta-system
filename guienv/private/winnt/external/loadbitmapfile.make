BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\loadBitmapFile.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\loadBitmapFile.obj: $(SRCDIR)\loadBitmapFile.c