BASEDIR	= $(SRCDIR)
MACHDIR	= $(BASEDIR)\$(MACHINETYPE)
OBJDIR	= $(MACHDIR)\$(SDK)

make: $(MACHDIR) $(OBJDIR) $(OBJDIR)\ctstcproc.obj

$(OBJDIR)\ctstcproc.obj: $(SRCDIR)\ctstcproc.c
	$(CC) -c $(CALIGN) $(CFLAGS) $(COUTPUT)$@ $?

$(MACHDIR) $(OBJDIR):
	if not exist $@\nul mkdir $@
