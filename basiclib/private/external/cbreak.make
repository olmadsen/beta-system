CC = gcc -O6
LD = ld
BASEDIR = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/cbreak.o

$(BASEDIR)/$(MACHINETYPE)/cbreak.o: $(BASEDIR)/external/cbreak/my_getch.c $(BASEDIR)/external/cbreak/my_gets.c $(BASEDIR)/external/cbreak/mystrings.c $(BASEDIR)/external/cbreak/sysdefs.h
	cd $(BASEDIR)/external/cbreak; make
	$(LD) -r -o $(BASEDIR)/$(MACHINETYPE)/cbreak.o $(BASEDIR)/external/cbreak/my_getch.o $(BASEDIR)/external/cbreak/my_gets.o $(BASEDIR)/external/cbreak/mystrings.o
	cd $(BASEDIR)/external/cbreak; make clean
