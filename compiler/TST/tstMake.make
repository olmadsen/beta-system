BASEDIR=.

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(BASEDIR)/$(MACHINETYPE)/ctstcproc.o: $(BASEDIR)/ctstcproc.c 
	gcc -c -O -o $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o $(BASEDIR)/ctstcproc.c
