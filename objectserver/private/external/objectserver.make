CC        = gcc -O 
dir   = $(BETALIB)/objectserver/v2.11/private
extdir = $(dir)/external/
odir = $(dir)/$(MACHINETYPE)/

make: $(odir)runAlloc_$(MACHINETYPE).o $(odir)searchHack.o $(odir)lazyref_gc.o 

$(odir)searchHack.o: $(extdir)searchHack.c
	$(CC) -D$(MACHINETYPE) -c -o $(odir)searchHack.o $(extdir)searchHack.c

$(odir)lazyref_gc.o: $(extdir)lazyref_gc.c
	$(CC) -D$(MACHINETYPE) -DRTLAZY -c -o $(odir)lazyref_gc.o $(extdir)lazyref_gc.c -I$(BETALIB)/betarun/v2.6/$(MACHINETYPE)/

$(odir)runAlloc_$(MACHINETYPE).o: $(extdir)runAlloc_$(MACHINETYPE).s
	as -o $(odir)runAlloc_$(MACHINETYPE).o $(extdir)runAlloc_$(MACHINETYPE).s

