CC        = gcc -O3
#CC        = cc -O
BASEDIR   = $(BETALIB)/basiclib/v1.5

make: $(BASEDIR)/$(MACHINETYPE)/ranlib.a

$(BASEDIR)/$(MACHINETYPE)/ranlib.a: $(BASEDIR)/$(MACHINETYPE)/ranlib.o 
	/bin/rm -f $(BASEDIR)/$(MACHINETYPE)/ranlib.a
	PATH=$PATH:/usr/ccs/bin; export PATH; ar r $(BASEDIR)/$(MACHINETYPE)/ranlib.a $(BASEDIR)/$(MACHINETYPE)/ranlib.o
	ranlib $(BASEDIR)/$(MACHINETYPE)/ranlib.a
	cp $(BASEDIR)/$(MACHINETYPE)/ranlib.a $(BASEDIR)/$(MACHINETYPE)/libranlib.a


$(BASEDIR)/$(MACHINETYPE)/ranlib.o: $(BASEDIR)/private/external/ranlib.c
	$(CC) -c -o $(BASEDIR)/$(MACHINETYPE)/ranlib.o $(BASEDIR)/private/external/ranlib.c
