CC        = gcc -O3
BASEDIR   = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/systemenvExt.o

$(BASEDIR)/$(MACHINETYPE)/systemenvExt.o: $(BASEDIR)/external/systemenvExt.c
	$(CC) -D$(MACHINETYPE) -c -o $(BASEDIR)/$(MACHINETYPE)/systemenvExt.o $(BASEDIR)/external/systemenvExt.c
