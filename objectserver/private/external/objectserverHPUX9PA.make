include objectserver.common.make

make: ../$(MACHINETYPE)/runAlloc_hpux9pa.o

../$(MACHINETYPE)/runAlloc_hpux9pa.o: runAlloc_hpux9pa.c
	$(CC) -c -I $(betarundir)/C -o ../$(MACHINETYPE)/runAlloc_hpux9pa.o runAlloc_hpux9pa.c

