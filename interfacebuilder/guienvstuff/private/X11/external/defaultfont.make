BASEDIR = $(BETALIB)interfacebuilder/v1.0/guienvstuff/private/X11
OBJDIR = $(BASEDIR)/$(MACHINETYPE)
SRCDIR = $(BASEDIR)/external

CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC) -O -g


defaultfont = $(OBJDIR)/defaultfont.o

$(defaultfont): $(SRCDIR)/defaultfont.c
	gcc $(CFLAGS) $(SRCDIR)/defaultfont.c -o $(defaultfont)
