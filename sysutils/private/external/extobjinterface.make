../$(MACHINETYPE)/extobjinterface.o:  extobjinterface.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) -c -o ../$(MACHINETYPE)/extobjinterface.o extobjinterface.c
