BASEDIR	   = $(BETALIB)/sysutils/v1.5/private
SRCDIR	   = $(BASEDIR)/external
OBJDIR	   = $(BASEDIR)/$(MACHINETYPE)
OBJS	   = $(OBJDIR)/scanobjects.o
BETARUNDIR = /users/beta/betarun/v2.7/$(MACHINETYPE)/C
CFLAGS	   = -O -g -I$(BETARUNDIR)

make: $(OBJS)

$(OBJDIR)/scanobjects.o: 
	gcc $(CFLAGS) -D$(MACHINETYPE) -c $(BETARUNDIR)/scanobjects.c \
	-o $(OBJDIR)/scanobjects.o

$(SRCDIR):
	mkdir $(BASEDIR)/$(MACHINETYPE)
