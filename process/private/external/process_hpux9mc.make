BETALIB	   = /users/beta
BASEDIR	   = $(BETALIB)/process/v1.5/private
SRCDIR	   = $(BASEDIR)/external
OBJDIR	   = $(BASEDIR)/$(MACHINETYPE)
OBJS	   = $(OBJDIR)/getHostAddr.o $(OBJDIR)/nonblock.o 
CFLAGS	   = -O -g
MACHINETYPE = hpux9mc

make: $(OBJS)

$(OBJDIR)/getHostAddr.o: $(SRCDIR)/getHostAddr.c
	gcc-2.5.8 $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/getHostAddr.c \
	-o $(OBJDIR)/getHostAddr.o

$(OBJDIR)/nonblock.o: $(SRCDIR)/nonblock.c
	gcc-2.5.8 $(CFLAGS) -D$(MACHINETYPE) -c $(SRCDIR)/nonblock.c \
	-o $(OBJDIR)/nonblock.o

$(SRCDIR):
	mkdir $(BASEDIR)/$(MACHINETYPE)
