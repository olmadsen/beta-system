../$(MACHINETYPE)/systemenvExt.o: ../$(MACHINETYPE) systemenvExt.c
	$(CC) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/systemenvExt.o systemenvExt.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

