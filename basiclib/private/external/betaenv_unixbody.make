../$(MACHINETYPE)/basicio.o: ../$(MACHINETYPE) basicio.c
	$(CC) -c -o ../$(MACHINETYPE)/basicio.o basicio.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

