BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\ntInt.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

CFLAGS = -DMACHINE=\"$(MACHINETYPE)\" $(CFLAGS)

$(OBJDIR)\ntInt.obj: $(SRCDIR)\ntInt.c
