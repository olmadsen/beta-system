BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\stdfiledlg.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\stdfiledlg.obj: $(SRCDIR)\stdfiledlg.c
