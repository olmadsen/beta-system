BETARUNDIR = /users/beta/betarun/v2.8/$(MACHINETYPE)/C
CFLAGS	   = -D$(MACHINETYPE) -I$(BETARUNDIR)

../$(MACHINETYPE)/scanobjects.o: 
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c $(CFLAGS) -o ../$(MACHINETYPE)/scanobjects.o $(BETARUNDIR)/scanobjects.c
