BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\basicio.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\basicio.obj: $(SRCDIR)\basicio.c
