../$(MACHINETYPE)/fileInt_unix.o: fileInt_unix.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/fileInt_unix.o fileInt_unix.c
