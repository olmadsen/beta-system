../$(MACHINETYPE)/systemenvExt.o: systemenvExt.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/systemenvExt.o systemenvExt.c
