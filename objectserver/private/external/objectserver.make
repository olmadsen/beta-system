CC        = gcc -O 
BASEDIR   = $(BETALIB)/objectserver/v2.11/private
EXTERNALDIR = $(BASEDIR)/external
OBJECTDIR = $(BASEDIR)/$(MACHINETYPE)

make: run rest
run: $(OBJECTDIR)/runAlloc_$(MACHINETYPE).o 
rest:$(OBJECTDIR)/searchHack.o $(OBJECTDIR)/lazyref_gc.o 

$(OBJECTDIR)/searchHack.o: $(EXTERNALDIR)/searchHack.c
	$(CC) -D$(MACHINETYPE) -c -o $(OBJECTDIR)/searchHack.o $(EXTERNALDIR)/searchHack.c

$(OBJECTDIR)/lazyref_gc.o: $(EXTERNALDIR)/lazyref_gc.c
	$(CC) -D$(MACHINETYPE) -DRTLAZY -c -o $(OBJECTDIR)/lazyref_gc.o $(EXTERNALDIR)/lazyref_gc.c -I$(BETALIB)/betarun/v2.6/$(MACHINETYPE)/

$(OBJECTDIR)/runAlloc_$(MACHINETYPE).o: $(EXTERNALDIR)/runAlloc_$(MACHINETYPE).s
	as -o $(OBJECTDIR)/runAlloc_$(MACHINETYPE).o $(EXTERNALDIR)/runAlloc_$(MACHINETYPE).s

