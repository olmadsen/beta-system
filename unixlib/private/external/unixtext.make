../$(MACHINETYPE)/unixtext.o:  unixtext.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/unixtext.o unixtext.c
