BASEDIR = $(SRCDIR)\..
BETARUNDIR = $(BETALIB)\betarun\v2.9\$(MACHINETYPE)\C

MAKEOBJS=$(OBJDIR)\scanobjects.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\scanobjects.obj: $(BETARUNDIR)\scanobjects.c
