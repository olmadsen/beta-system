../$(MACHINETYPE)/uniq.o: ../$(MACHINETYPE) uniq.c
	$(CC) -c -o ../$(MACHINETYPE)/uniq.o uniq.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

