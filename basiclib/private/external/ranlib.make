OBJDIR = ../$(MACHINETYPE)

$(OBJDIR)/ranlib.o: ranlib.c
	sh -c 'if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi'
	$(CC) -c -o $(OBJDIR)/ranlib.o ranlib.c
