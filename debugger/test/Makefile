CC	= gcc -g -I ../private/external -D$(objdir)

all: breaktest coretest

coreaccess.o: ../private/external/coreaccess.c ../private/external/coreaccess.h
	$(CC)  -c -o coreaccess.o ../private/external/coreaccess.c
breaktest: ../private/external/breaktest.c
	$(CC) -o breaktest ../private/external/breaktest.c
coretest: ../private/external/coretest.c coreaccess.o
	$(CC) -o coretest ../private/external/coretest.c coreaccess.o

clean:
	/bin/rm -f *~ core *.o
