
make: ../$(MACHINETYPE)/processComm.o ../$(MACHINETYPE)/getfileno.o 
      
../$(MACHINETYPE)/processComm.o: processComm.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=\"$(MACHINETYPE)\" -c  -o ../$(MACHINETYPE)/processComm.o processComm.c

../$(MACHINETYPE)/getfileno.o: getfileno.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=\"$(MACHINETYPE)\" -c  -o ../$(MACHINETYPE)/getfileno.o getfileno.c
