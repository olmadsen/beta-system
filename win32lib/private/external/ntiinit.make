BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\ntiinit.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\ntiinit.obj: $(SRCDIR)\ntiinit.c