BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\filedirmisc.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\filedirmisc.obj: $(SRCDIR)\filedirmisc.c
