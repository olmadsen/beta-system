OBJDIR = ../$(MACHINETYPE)

$(OBJDIR)/ranlib.a: $(OBJDIR)/ranlib.o 
	sh -c 'if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi'
	/bin/rm -f $(OBJDIR)/ranlib.a
	sh -c 'PATH=$${PATH}:/usr/ccs/bin; export PATH; ar r $(OBJDIR)/ranlib.a $(OBJDIR)/ranlib.o'
	ranlib $(OBJDIR)/ranlib.a
	cp $(OBJDIR)/ranlib.a $(OBJDIR)/libranlib.a

$(OBJDIR)/ranlib.o: ranlib.c
	$(CC) -c -o $(OBJDIR)/ranlib.o ranlib.c
