sparc_disass.o: ../sparc_disass.c
	gcc -g -c -O6 -Wall -o sparc_disass.o -DBETA ../sparc_disass.c

sparc_disass: ../sparc_disass.c
	gcc -g -O6 -Wall -o sparc_disass -DBETA -DMAIN ../sparc_disass.c

read-aout.o: read-aout.c
	gcc -g -c -O6 -o read-aout.o read-aout.c
read-aout.i: read-aout.c
	gcc -E -save-temps -H -dD read-aout.c > read-aout.i

read-aout: read-aout.o sparc_disass.o
	gcc -g -o read-aout read-aout.o sparc_disass.o

fisk.o:
	gcc -o fisk.o -c fisk.c

clean:
	/bin/rm -f *.o *~ core *.ast *.dump *.lst
