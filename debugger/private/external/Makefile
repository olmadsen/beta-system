CC        = gcc -g -O 
BASEDIR   = $(BETALIB)/debugger/v2.0/private
EXTERNALDIR = $(BASEDIR)/external
OBJECTDIR = $(BASEDIR)/$(MACHINETYPE)

$(OBJECTDIR)/coreaccess_$(MACHINETYPE).o: $(EXTERNALDIR)/coreaccess_$(MACHINETYPE).c $(EXTERNALDIR)/coreaccess_$(MACHINETYPE).h
	gcc -D$(MACHINETYPE) -c -o $(OBJECTDIR)/coreaccess_$(MACHINETYPE).o $(EXTERNALDIR)/coreaccess_$(MACHINETYPE).c