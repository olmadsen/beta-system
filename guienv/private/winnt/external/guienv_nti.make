BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\guienv_nti.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\guienv_nti.obj: $(SRCDIR)\guienv_nti.c