BASEDIR	= $(SRCDIR)\..

MAKEOBJS= $(OBJDIR)\dirInt.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\dirInt.obj: $(SRCDIR)\dirInt.c
