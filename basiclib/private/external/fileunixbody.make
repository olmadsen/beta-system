../$(MACHINETYPE)/fileInt.o: fileInt.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/fileInt.o fileInt.c
