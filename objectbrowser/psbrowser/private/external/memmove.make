../$(MACHINETYPE)/memmove.o: memmove.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/memmove.o memmove.c
