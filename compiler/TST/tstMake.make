BASEDIR=.

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(BASEDIR)/$(MACHINETYPE)/ctstcproc.o: $(BASEDIR)/ctstcproc.c 
	$(CC) -c -o -o $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o $(BASEDIR)/ctstcproc.c

