BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\regexpr.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\regexpr.obj: $(SRCDIR)\regexpr.c
