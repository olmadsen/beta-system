BASEDIR	= $(SRCDIR)

MAKEOBJS = $(OBJDIR)\ctstcproc.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\ctstcproc.obj: $(SRCDIR)\ctstcproc.c
