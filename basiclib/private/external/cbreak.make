LD = ld

../$(MACHINETYPE)/cbreak.o: ../$(MACHINETYPE) cbreak/my_getch.c cbreak/my_gets.c cbreak/mystrings.c cbreak/sysdefs.h
	cd cbreak; make
	$(LD) -r -o ../$(MACHINETYPE)/cbreak.o cbreak/my_getch.o cbreak/my_gets.o cbreak/mystrings.o
	cd cbreak; make clean

../$(MACHINETYPE):
	mkdir ../$(MACHINETYPE)

