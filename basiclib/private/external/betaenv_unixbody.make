../$(MACHINETYPE)/basicio.o: basicio.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/basicio.o basicio.c

