../$(MACHINETYPE)/startAsDeamon: ../$(MACHINETYPE)/startAsDeamon.o ../$(MACHINETYPE)/deamonStart.o 
	$(CC) -D$(MACHINETYPE) ../$(MACHINETYPE)/startAsDeamon.o ../$(MACHINETYPE)/deamonStart.o -o ../$(MACHINETYPE)/startAsDeamon

../$(MACHINETYPE)/startAsDeamon.o: startAsDeamon.c
	$(CC) -D$(MACHINETYPE)  -c startAsDeamon.c -o ../$(MACHINETYPE)/startAsDeamon.o
	
../$(MACHINETYPE)/deamonStart.o: deamonStart.c
	$(CC) -D$(MACHINETYPE)  -c deamonStart.c -o ../$(MACHINETYPE)/deamonStart.o
	
