CC        = gcc -g 
BASEDIR   = $(BETALIB)/debugger/v2.0/private
EXTERNALDIR = $(BASEDIR)/external
OBJECTDIR = $(BASEDIR)/$(MACHINETYPE)

make: $(OBJECTDIR)/processComm.o $(OBJECTDIR)/getfileno.o 
      
$(OBJECTDIR)/processComm.o: $(EXTERNALDIR)/processComm.c  
	$(CC) -D$(MACHINETYPE) -c $(EXTERNALDIR)/processComm.c -o $(OBJECTDIR)/processComm.o 
    
$(OBJECTDIR)/getfileno.o: $(EXTERNALDIR)/getfileno.c  
	$(CC) -D$(MACHINETYPE) -c $(EXTERNALDIR)/getfileno.c -o $(OBJECTDIR)/getfileno.o 

$(OBJECTDIR): 
	mkdir $(OBJECTDIR)
