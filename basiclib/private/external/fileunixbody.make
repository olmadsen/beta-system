../$(MACHINETYPE)/fileInt.o: ../$(MACHINETYPE) fileInt.c
	$(CC) -c -o ../$(MACHINETYPE)/fileInt.o fileInt.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

