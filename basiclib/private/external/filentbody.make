BASEDIR	= $(SRCDIR)\..

MAKEOBJS = $(OBJDIR)\fileInt_nt.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\fileInt_nt.obj: $(SRCDIR)\fileInt_nt.c
