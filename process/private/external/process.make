CFLAGS	   = 
OBJS	   = ../$(MACHINETYPE)/getHostAddr.o ../$(MACHINETYPE)/nonblock.o 

make: $(OBJS)

../$(MACHINETYPE)/getHostAddr.o: getHostAddr.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) $(CFLAGS) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/getHostAddr.o getHostAddr.c

../$(MACHINETYPE)/nonblock.o: nonblock.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) $(CFLAGS) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/nonblock.o nonblock.c
