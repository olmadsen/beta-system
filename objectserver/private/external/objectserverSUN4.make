CC        = gcc -O 
dir   = $(BETALIB)/objectserver/v2.11/private
extdir = $(dir)/external/
odir = $(dir)/$(MACHINETYPE)/

make: $(odir)searchHack.o $(odir)lazyref_gc.o 

$(odir)searchHack.o: $(extdir)searchHack.c
	$(CC) -D$(MACHINETYPE) -c -o $(odir)searchHack.o $(extdir)searchHack.c

$(odir)lazyref_gc.o: $(extdir)lazyref_gc.c
	$(CC) -D$(MACHINETYPE) -DRTLAZY -c -o $(odir)lazyref_gc.o $(extdir)lazyref_gc.c -I/users/beta/betarun/v2.6/$(MACHINETYPE)/
