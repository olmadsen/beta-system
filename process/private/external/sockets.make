CFLAGS	   = 

OBJS       = ../$(MACHINETYPE)/sockSignals.o ../$(MACHINETYPE)/sockets.o

make: $(OBJS)

../$(MACHINETYPE)/sockSignals.o: sockSignals.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) $(CFLAGS) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/sockSignals.o sockSignals.c

../$(MACHINETYPE)/sockets.o:  sockets.c
	sh -c 'if [ ! -d ../$(MACHINETYPE) ]; then mkdir ../$(MACHINETYPE); fi'
	$(CC) $(CFLAGS) -D$(MACHINETYPE) -c -o ../$(MACHINETYPE)/sockets.o sockets.c
