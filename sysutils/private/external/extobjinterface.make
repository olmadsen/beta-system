BASEDIR = $(BETALIB)/sysutils/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/extobjinterface.o 

$(BASEDIR)/$(MACHINETYPE)/extobjinterface.o: $(BASEDIR)/external/extobjinterface.c
	gcc -O -c -o $(BASEDIR)/$(MACHINETYPE)/extobjinterface.o $(BASEDIR)/external/extobjinterface.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)

