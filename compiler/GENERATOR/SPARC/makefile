sparc_disass.o: sparc_disass.c
	gcc -c -O6 -Wall -o sparc_disass.o -DBETA sparc_disass.c
sparc_disass: sparc_disass.c
	gcc -O6 -Wall -o sparc_disass -DBETA -DMAIN sparc_disass.c
debug: sparc_disass.c
	gcc -g -O0 -Wall -o sparc_disass -DBETA -DMAIN sparc_disass.c
