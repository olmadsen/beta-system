odir = ../$(MACHINETYPE)/
debug =

make: $(odir)extShellSockets.o $(odir)getUser.o \
      $(odir)remoteStart.o $(odir)outputRedirection.o \
      $(odir)timing.o $(odir)thisHost.o \
      $(MACHINETYPE)/startAsDeamon
      
$(odir)getUser.o: getUser.c
	$(CC) $(debug) -D$(MACHINETYPE) -c getUser.c -o $(odir)getUser.o

$(odir)outputRedirection.o: outputRedirection.c
	$(CC) $(debug) -D$(MACHINETYPE) -c outputRedirection.c -o $(odir)outputRedirection.o 

$(odir)timing.o: timing.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c timing.c -o $(odir)timing.o

$(odir)extShellSockets.o: extShellSockets.c extShellSockets.h
	$(CC) $(debug) -D$(MACHINETYPE)  -c extShellSockets.c -o $(odir)extShellSockets.o

$(odir)remoteStart.o: remoteStart.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c remoteStart.c -o $(odir)remoteStart.o

$(odir)deamonStart.o: deamonStart.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c deamonStart.c -o $(odir)deamonStart.o

$(odir)startAsDeamon.o: startAsDeamon.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c startAsDeamon.c -o $(odir)startAsDeamon.o
	
$(odir)thisHost.o: thisHost.c
	$(CC) $(debug) -D$(MACHINETYPE) -I $(BETALIB)/process/v1.5/private/external  -c thisHost.c -o $(odir)thisHost.o

$(MACHINETYPE)/startAsDeamon: $(odir)startAsDeamon.o $(odir)deamonStart.o 
	-sh -c 'if [ ! -d $(MACHINETYPE) ]; then mkdir $(MACHINETYPE); fi'
	$(CC) $(debug) -D$(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o -o $(MACHINETYPE)/startAsDeamon
