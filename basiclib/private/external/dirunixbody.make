CC        = gcc -O3
#CC        = cc -O

BASEDIR   = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/dirInt.o

$(BASEDIR)/$(MACHINETYPE)/dirInt.o: $(BASEDIR)/external/dirInt.c
	$(CC) -c -O -o $(BASEDIR)/$(MACHINETYPE)/dirInt.o $(BASEDIR)/external/dirInt.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)
