BASEDIR = $(SRCDIR)\..

MAKEOBJS=$(OBJDIR)\getUser.obj\
	 $(OBJDIR)\outputRedirection.obj\
	 $(OBJDIR)\deamonStart_nti.obj

!include <$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make>

$(OBJDIR)\getUser.obj:			$(SRCDIR)\getUser.c

$(OBJDIR)\outputRedirection.obj:	$(SRCDIR)\outputRedirection.c

$(OBJDIR)\deamonStart_nti.obj:		$(SRCDIR)\deamonStart_nti.c