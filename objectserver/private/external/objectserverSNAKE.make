include objectserver.common.make

../$(MACHINETYPE)/runAlloc_snake.o: runAlloc_snake.c
	$(CC) -c -I $(betarundir)/C -o ../$(MACHINETYPE)/runAlloc_snake.o runAlloc_snake.c

