../$(MACHINETYPE)/dirInt.o: dirInt.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/dirInt.o dirInt.c
