betarundir = $(BETALIB)/betarun/v2.7/$(MACHINETYPE)

make: ../$(MACHINETYPE)/searchHack.o ../$(MACHINETYPE)/lazyref_gc.o 

../$(MACHINETYPE)/searchHack.o: searchHack.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/searchHack.o searchHack.c

../$(MACHINETYPE)/lazyref_gc.o:
	$(CC) -I$(betarundir) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/lazyref_gc.o $(betarundir)/C/lazyref_gc.c 
