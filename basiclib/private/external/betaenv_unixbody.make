CC        = gcc -O3
BASEDIR   = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/basicio.o

$(BASEDIR)/$(MACHINETYPE)/basicio.o: $(BASEDIR)/external/basicio.c
	$(CC) -c -O -o $(BASEDIR)/$(MACHINETYPE)/basicio.o $(BASEDIR)/external/basicio.c
