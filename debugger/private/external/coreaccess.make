CC=gcc -g -O 
BASEDIR=$(BETALIB)/debugger/v2.0/private
EXTERNALDIR=$(BASEDIR)/external
OBJECTDIR=$(BASEDIR)/$(MACHINETYPE)

make: $(OBJECTDIR)/coreaccess.o

$(OBJECTDIR)/coreaccess.o: $(OBJECTDIR) $(EXTERNALDIR)/coreaccess.c $(EXTERNALDIR)/coreaccess.h
	gcc -D$(MACHINETYPE) -c -o $(OBJECTDIR)/coreaccess.o $(EXTERNALDIR)/coreaccess.c

$(OBJECTDIR): 
	mkdir $(OBJECTDIR)
