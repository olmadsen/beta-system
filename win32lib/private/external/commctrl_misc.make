BASEDIR	= $(SRCDIR)\..
MAKEOBJS=$(OBJDIR)\commctrl_misc.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\commctrl_misc.obj: $(SRCDIR)\commctrl_misc.c
