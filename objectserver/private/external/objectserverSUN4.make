CC        = gcc -O 
BASEDIR   = $(BETALIB)/objectserver/v2.11/private
EXTERNALDIR = $(BASEDIR)/external
OBJECTDIR = $(BASEDIR)/$(MACHINETYPE)

rest:$(OBJECTDIR)/searchHack.o $(OBJECTDIR)/lazyref_gc.o 

$(OBJECTDIR)/searchHack.o: $(EXTERNALDIR)/searchHack.c
	$(CC) -D$(MACHINETYPE) -c -o $(OBJECTDIR)/searchHack.o $(EXTERNALDIR)/searchHack.c

$(OBJECTDIR)/lazyref_gc.o: $(EXTERNALDIR)/lazyref_gc.c
	$(CC) -D$(MACHINETYPE) -DRTLAZY -c -o $(OBJECTDIR)/lazyref_gc.o $(EXTERNALDIR)/lazyref_gc.c -I/users/beta/betarun/v2.6/$(MACHINETYPE)/
