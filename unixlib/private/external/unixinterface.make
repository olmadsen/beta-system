../$(MACHINETYPE)/unixInt.o:  unixInt.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/unixInt.o unixInt.c
