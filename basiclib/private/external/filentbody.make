BASEDIR	= $(SRCDIR)\..

MAKEOBJS = $(OBJDIR)\fileInt.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\fileInt.obj: $(SRCDIR)\fileInt.c
