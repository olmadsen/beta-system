make: ../$(MACHINETYPE)/labelnametable.o

../$(MACHINETYPE)/labelnametable.o: labelnametable.c 
	$(CC) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/labelnametable.o labelnametable.c
