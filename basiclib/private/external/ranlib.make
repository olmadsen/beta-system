../$(MACHINETYPE)/ranlib.a: ../$(MACHINETYPE): ../$(MACHINETYPE)/ranlib.o 
	/bin/rm -f ../$(MACHINETYPE)/ranlib.a
	PATH=$$PATH:/usr/ccs/bin; export PATH; ar r ../$(MACHINETYPE)/ranlib.a ../$(MACHINETYPE)/ranlib.o
	ranlib ../$(MACHINETYPE)/ranlib.a
	cp ../$(MACHINETYPE)/ranlib.a ../$(MACHINETYPE)/libranlib.a


../$(MACHINETYPE)/ranlib.o: ranlib.c
	$(CC) -c -o ../$(MACHINETYPE)/ranlib.o ranlib.c

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

