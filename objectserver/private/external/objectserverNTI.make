BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\lazyref_gc.obj $(OBJDIR)\runAlloc_$(MACHINETYPE).obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

CFLAGS=$(CFLAGS) -I$(BETALIB)\BI

$(OBJDIR)\lazyref_gc.obj: $(BETARUNDIR)\C\lazyref_gc.c

$(OBJDIR)\runAlloc_$(MACHINETYPE).obj: $(SRCDIR)\runAlloc_$(MACHINETYPE).asm
