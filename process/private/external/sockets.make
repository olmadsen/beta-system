BASEDIR	   = $(BETALIB)/process/v1.5/private
SRCDIR	   = $(BASEDIR)/external
OBJDIR	   = $(BASEDIR)/$(MACHINETYPE)
OBJS	   = $(OBJDIR)/sockets.o $(OBJDIR)/sockSignals.o 
CFLAGS	   = -O

make: $(OBJS)

$(OBJDIR)/sockets.o: $(SRCDIR)/sockets.c
	gcc $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/sockets.c \
	-o $(OBJDIR)/sockets.o

$(OBJDIR)/sockSignals.o: $(SRCDIR)/sockSignals.c
	gcc $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/sockSignals.c \
	-o $(OBJDIR)/sockSignals.o

$(SRCDIR):
	mkdir $(BASEDIR)/$(MACHINETYPE)
