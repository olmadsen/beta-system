../$(MACHINETYPE)/regexpr.o: ../$(MACHINETYPE) regexpr.c
	$(CC) -c -o ../$(MACHINETYPE)/regexpr.o regexpr.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

