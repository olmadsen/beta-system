CC = gcc -03
#CC = cc -O
BASEDIR = $(BETALIB)/basiclib/v1.5/private
make: $(BASEDIR)/$(MACHINETYPE)/uniq.o

$(BASEDIR)/$(MACHINETYPE)/uniq.o: $(BASEDIR)/external/uniq.c
	$(CC) -c -O -o $(BASEDIR)/$(MACHINETYPE)/uniq.o $(BASEDIR)/external/uniq.c
