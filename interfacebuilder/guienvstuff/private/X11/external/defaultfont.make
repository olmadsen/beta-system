BASEDIR = ..
OBJDIR = $(BASEDIR)/$(MACHINETYPE)
SRCDIR = $(BASEDIR)/external

CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC) -O -g


defaultfont = $(OBJDIR)/defaultfont.o

$(defaultfont): $(SRCDIR)/defaultfont.c
	$(CC) $(CFLAGS) $(SRCDIR)/defaultfont.c -o $(defaultfont)
