make: $(MACHINETYPE)/ctstcproc.o

$(MACHINETYPE)/ctstcproc.o: ctstcproc.c
	cc -c -O -o $(MACHINETYPE)/ctstcproc.o ctstcproc.c
