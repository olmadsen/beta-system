BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\extobjinterface.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\extobjinterface.obj: $(SRCDIR)\extobjinterface.c

