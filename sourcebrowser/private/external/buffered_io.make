../$(MACHINETYPE)/getfileno.o: getfileno.c  
	$(CC) -D$(MACHINETYPE) -DMACHINETYPE=\"$(MACHINETYPE)\" -c  -o ../$(MACHINETYPE)/getfileno.o getfileno.c
