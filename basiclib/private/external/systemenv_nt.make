BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\systemenvExt.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\systemenvExt.obj: $(SRCDIR)\systemenvExt.c
