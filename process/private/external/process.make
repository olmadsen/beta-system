BASEDIR	   = $(BETALIB)/process/v1.4.1/private
SRCDIR	   = $(BASEDIR)/external
OBJDIR	   = $(BASEDIR)/$(MACHINETYPE)
OBJS	   = $(OBJDIR)/getHostAddr.o $(OBJDIR)/nonblock.o 
CFLAGS	   = -O -g

make: $(OBJS)

$(OBJDIR)/getHostAddr.o: $(SRCDIR)/getHostAddr.c
	gcc $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/getHostAddr.c \
	-o $(OBJDIR)/getHostAddr.o

$(OBJDIR)/nonblock.o: $(SRCDIR)/nonblock.c
	gcc $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/nonblock.c \
	-o $(OBJDIR)/nonblock.o

$(SRCDIR):
	mkdir $(BASEDIR)/$(MACHINETYPE)
