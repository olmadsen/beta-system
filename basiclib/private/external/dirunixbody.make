../$(MACHINETYPE)/dirInt.o: ../$(MACHINETYPE) dirInt.c
	$(CC) -c -o ../$(MACHINETYPE)/dirInt.o dirInt.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)
