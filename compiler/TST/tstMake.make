<<<<<<< tstMake.make
BASEDIR=.

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(BASEDIR)/$(MACHINETYPE)/ctstcproc.o: $(BASEDIR)/ctstcproc.c 
	$(CC) -c -o $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o $(BASEDIR)/ctstcproc.c
=======
$(MACHINETYPE)/ctstcproc.o: ctstcproc.c 
	$(CC) -c -o $(MACHINETYPE)/ctstcproc.o ctstcproc.c
>>>>>>> 1.8

