BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\convert_nti.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\convert_nti.obj: $(SRCDIR)\convert_nti.c
