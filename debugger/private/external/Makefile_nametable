CC=gcc -g -O 
BASEDIR=$(BETALIB)/debugger/v2.0/private
EXTERNALDIR=$(BASEDIR)/external
OBJECTDIR=$(BASEDIR)/$(MACHINETYPE)

make: $(OBJECTDIR)/labelnametable.o

$(OBJECTDIR)/labelnametable.o: $(OBJECTDIR) $(EXTERNALDIR)/labelnametable.c 
	gcc -D$(MACHINETYPE) -c -o $(OBJECTDIR)/labelnametable.o $(EXTERNALDIR)/labelnametable.c

$(OBJECTDIR): 
	mkdir $(OBJECTDIR)
