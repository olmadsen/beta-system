odir = ../$(MACHINETYPE)/
debug =

make: $(odir)extShellSockets.o $(odir)getUser.o \
      $(odir)remoteStart.o $(odir)outputRedirection.o \
      $(odir)timing.o $(odir)thisHost.o \
      $(MACHINETYPE) $(MACHINETYPE)/startAsDeamon

$(MACHINETYPE):
	-sh -c 'if [ ! -d $(MACHINETYPE) ]; then mkdir $(MACHINETYPE); fi'

$(odir)getUser.o: getUser.c
	gcc $(debug) -D$(MACHINETYPE) -c getUser.c -o $(odir)getUser.o

$(odir)outputRedirection.o: outputRedirection.c
	gcc $(debug) -D$(MACHINETYPE) -c outputRedirection.c -o $(odir)outputRedirection.o 

$(odir)timing.o: timing.c
	gcc $(debug) -D$(MACHINETYPE) -O -c timing.c -o $(odir)timing.o

$(odir)extShellSockets.o: extShellSockets.c extShellSockets.h
	gcc $(debug) -D$(MACHINETYPE) -O -c extShellSockets.c -o $(odir)extShellSockets.o

$(odir)remoteStart.o: remoteStart.c
	gcc $(debug) -D$(MACHINETYPE) -O -c remoteStart.c -o $(odir)remoteStart.o

$(odir)deamonStart.o: deamonStart.c
	gcc $(debug) -D$(MACHINETYPE) -O -c deamonStart.c -o $(odir)deamonStart.o

$(odir)startAsDeamon.o: startAsDeamon.c
	gcc $(debug) -D$(MACHINETYPE) -O -c startAsDeamon.c -o $(odir)startAsDeamon.o
	
$(odir)thisHost.o: thisHost.c
	gcc $(debug) -D$(MACHINETYPE) -I $(BETALIB)/process/v1.5/private/external -O -c thisHost.c -o $(odir)thisHost.o

$(MACHINETYPE)/startAsDeamon: $(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o 
	gcc $(debug) -D$(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o -o $(MACHINETYPE)/startAsDeamon
