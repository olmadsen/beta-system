../$(MACHINETYPE)/assignRef.o: ../$(MACHINETYPE) assignRef.c
	$(CC) -c -o ../$(MACHINETYPE)/assignRef.o assignRef.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

