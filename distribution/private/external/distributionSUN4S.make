dir = $(BETALIB)/distribution/v1.0/private/external/
odir = $(BETALIB)/distribution/v1.0/private/$(MACHINETYPE)/
debug =

make: $(odir)extShellSockets.o $(odir)getUser.o \
      $(odir)dot.o $(odir)remoteStart.o $(odir)outputRedirection.o \
      $(odir)timing.o $(odir)thisHost.o $(dir)$(MACHINETYPE)/startAsDeamon \
      $(dir)$(MACHINETYPE)

$(odir)dot.o: $(dir)dot.c $(dir)dot.h
	gcc $(dir)dot.c -o $(odir)dot.o -c $(debug) -D$(MACHINETYPE) -O -I$(BETALIB)/betarun/v2.6/$(MACHINETYPE)/C/

$(odir)getUser.o: $(dir)getUser.c
	gcc $(debug) -D$(MACHINETYPE) -c $(dir)getUser.c -o $(odir)getUser.o

$(odir)outputRedirection.o: $(dir)outputRedirection.c
	gcc $(debug) -D$(MACHINETYPE) -c $(dir)outputRedirection.c -o $(odir)outputRedirection.o 

$(odir)timing.o: $(dir)timing.c
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)timing.c -o $(odir)timing.o

$(odir)extShellSockets.o: $(dir)extShellSockets.c $(dir)extShellSockets.h
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)extShellSockets.c -o $(odir)extShellSockets.o

$(odir)remoteStart.o: $(dir)remoteStart.c
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)remoteStart.c -o $(odir)remoteStart.o

$(odir)deamonStart.o: $(dir)deamonStart.c
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)deamonStart.c -o $(odir)deamonStart.o

$(odir)startAsDeamon.o: $(dir)startAsDeamon.c
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)startAsDeamon.c -o $(odir)startAsDeamon.o
	
$(odir)thisHost.o: $(dir)thisHost.c
	gcc $(debug) -D$(MACHINETYPE) -O -c $(dir)thisHost.c -o $(odir)thisHost.o

$(dir)$(MACHINETYPE):
	mkdir $(dir)$(MACHINETYPE)

$(dir)$(MACHINETYPE)/startAsDeamon: $(odir)startAsDeamon.o $(odir)deamonStart.o 
	gcc $(debug) -D$(MACHINETYPE) $(odir)startAsDeamon.o $(odir)deamonStart.o -o $(dir)$(MACHINETYPE)/startAsDeamon
