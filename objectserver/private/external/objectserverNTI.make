BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\searchHack.obj $(OBJDIR)\lazyref_gc.obj $(OBJDIR)\runAlloc_$(MACHINETYPE).obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

CFLAGS=$(CFLAGS) -I$(BETALIB)\BI

$(OBJDIR)\searchHack.obj: $(SRCDIR)\searchHack.c

$(OBJDIR)\lazyref_gc.obj: $(BETARUNDIR)\C\lazyref_gc.c

$(OBJDIR)\runAlloc_$(MACHINETYPE).obj: $(SRCDIR)\runAlloc_$(MACHINETYPE).asm
