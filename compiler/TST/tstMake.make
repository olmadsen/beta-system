#BASEDIR=/users/olm/beta/system/v5.0/TST
BASEDIR=$(BETALIB)/betarun/v2.6/$(MACHINETYPE)/TST

make: $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o

$(BASEDIR)/$(MACHINETYPE)/ctstcproc.o: $(BASEDIR)/ctstcproc.c
	cc -c -O -o $(BASEDIR)/$(MACHINETYPE)/ctstcproc.o $(BASEDIR)/ctstcproc.c
