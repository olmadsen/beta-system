BASEDIR	= $(SRCDIR)\..

MAKEOBJS = $(OBJDIR)\ntText.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\ntText.obj: $(SRCDIR)\ntText.c
