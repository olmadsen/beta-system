
make: ../$(MACHINETYPE)/processComm.o ../$(MACHINETYPE)/getfileno.o 
      
../$(MACHINETYPE)/processComm.o: processComm.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=$(MACHINETYPE) -c  -o ../$(MACHINETYPE)/processComm.o processComm.c

../$(MACHINETYPE)/getFileno.o: getFileno.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=$(MACHINETYPE) -c  -o ../$(MACHINETYPE)/getFileno.o getFileno.c
