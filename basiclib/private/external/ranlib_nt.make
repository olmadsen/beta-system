BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\ranlib.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\ranlib.obj: $(SRCDIR)\ranlib.c
