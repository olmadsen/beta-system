
make: ../$(MACHINETYPE)/coreaccess.o

../$(MACHINETYPE)/coreaccess.o: coreaccess.c coreaccess.h
	$(CC) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/coreaccess.o coreaccess.c
