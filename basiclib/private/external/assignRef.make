../$(MACHINETYPE)/assignRef.o: assignRef.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/assignRef.o assignRef.c

