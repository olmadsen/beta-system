dir = ./
odir = ../$(MACHINETYPE)/
debug =

make: $(odir)extShellSockets.o $(odir)getUser.o \
      $(odir)remoteStart.o $(odir)outputRedirection.o \
      $(odir)timing.o $(odir)thisHost.o $(dir)$(MACHINETYPE) \
      $(dir)$(MACHINETYPE)/startAsDeamon
      
$(dir)$(MACHINETYPE):
	mkdir $(dir)$(MACHINETYPE)

$(odir)getUser.o: $(dir)getUser.c
	$(CC) $(debug) -D$(MACHINETYPE) -c $(dir)getUser.c -o $(odir)getUser.o

$(odir)outputRedirection.o: $(dir)outputRedirection.c
	$(CC) $(debug) -D$(MACHINETYPE) -c $(dir)outputRedirection.c -o $(odir)outputRedirection.o 

$(odir)timing.o: $(dir)timing.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c $(dir)timing.c -o $(odir)timing.o

$(odir)extShellSockets.o: $(dir)extShellSockets.c $(dir)extShellSockets.h
	$(CC) $(debug) -D$(MACHINETYPE)  -c $(dir)extShellSockets.c -o $(odir)extShellSockets.o

$(odir)remoteStart.o: $(dir)remoteStart.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c $(dir)remoteStart.c -o $(odir)remoteStart.o

$(odir)deamonStart.o: $(dir)deamonStart.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c $(dir)deamonStart.c -o $(odir)deamonStart.o

$(odir)startAsDeamon.o: $(dir)startAsDeamon.c
	$(CC) $(debug) -D$(MACHINETYPE)  -c $(dir)startAsDeamon.c -o $(odir)startAsDeamon.o
	
$(odir)thisHost.o: $(dir)thisHost.c
	$(CC) $(debug) -D$(MACHINETYPE) -I $(BETALIB)/process/v1.4/private/external  -c $(dir)thisHost.c -o $(odir)thisHost.o

$(dir)$(MACHINETYPE)/startAsDeamon: $(dir)$(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o 
	$(CC) $(debug) -D$(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o -o $(dir)$(MACHINETYPE)/startAsDeamon
