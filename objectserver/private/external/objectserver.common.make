betarundir = $(BETALIB)/betarun/v2.9/$(MACHINETYPE)

make: ../$(MACHINETYPE)/lazyref_gc.o 

../$(MACHINETYPE)/lazyref_gc.o:
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -I$(betarundir) -c -o ../$(MACHINETYPE)/lazyref_gc.o $(betarundir)/C/lazyref_gc.c 
