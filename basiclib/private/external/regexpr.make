CC        = gcc -O3
#CC        = cc -O
BASEDIR   = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/regexpr.o

$(BASEDIR)/$(MACHINETYPE)/regexpr.o: $(BASEDIR)/external/regexpr.c
	$(CC) -c -o $(BASEDIR)/$(MACHINETYPE)/regexpr.o $(BASEDIR)/external/regexpr.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)
