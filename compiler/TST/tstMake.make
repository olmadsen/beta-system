BASEDIR=.

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(MACHINETYPE)/ctstcproc.o: ctstcproc.c 
	$(CC) -c -o $(MACHINETYPE)/ctstcproc.o ctstcproc.c

