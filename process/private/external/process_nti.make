BASEDIR	= $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\getHostAddr.obj $(OBJDIR)\nonblock.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\getHostAddr.obj: $(SRCDIR)\getHostAddr.c

$(OBJDIR)\nonblock.obj: $(SRCDIR)\nonblock.c
