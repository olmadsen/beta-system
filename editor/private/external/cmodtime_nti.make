BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\cmodtime.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\cmodtime.obj: $(SRCDIR)\cmodtime.c

