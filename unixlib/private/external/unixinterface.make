../$(MACHINETYPE)/unixInt.o:  unixInt.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -D$(MACHINETYPE) -DMACHINE=\"$(MACHINETYPE)\" -o ../$(MACHINETYPE)/unixInt.o unixInt.c
