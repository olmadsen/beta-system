CC        = gcc -O3
#CC        = cc -O
BASEDIR   = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/fileInt.o

$(BASEDIR)/$(MACHINETYPE)/fileInt.o: $(BASEDIR)/external/fileInt.c
	$(CC) -c -o $(BASEDIR)/$(MACHINETYPE)/fileInt.o $(BASEDIR)/external/fileInt.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)
