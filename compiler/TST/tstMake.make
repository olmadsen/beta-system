BASEDIR=.
#BASEDIR=$(BETALIB)/betarun/v2.6/$(MACHINETYPE)/TST

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(BASEDIR)/$(MACHINETYPE)/ctstcproc.o: $(BASEDIR)/ctstcproc.c $(BASEDIR)/$(MACHINETYPE)
	gcc -c -O -o $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o $(BASEDIR)/ctstcproc.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)
