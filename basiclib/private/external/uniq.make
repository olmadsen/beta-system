../$(MACHINETYPE)/uniq.o:  uniq.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/uniq.o uniq.c
	

