BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\scanobjects.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\scanobjects.obj: $(BETARUNDIR)\C\scanobjects.c
