../$(MACHINETYPE)/processComm.o: processComm.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=\"$(MACHINETYPE)\" -c  -o ../$(MACHINETYPE)/processComm.o processComm.c
