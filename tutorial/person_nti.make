BASEDIR = . 
MAKEOBJS=$(OBJDIR)\cperson.obj 
!include<$(BETALIB)\bin\$(SDK)\rules$(ASM_VERSION).make> 
$(OBJDIR)\cperson.obj: $(SRCDIR)\cperson.c 
