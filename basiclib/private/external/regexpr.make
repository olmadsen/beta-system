../$(MACHINETYPE)/regexpr.o: regexpr.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/regexpr.o regexpr.c
