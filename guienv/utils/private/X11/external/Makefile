BASEDIR = $(BETALIB)/guienv/v1.2/utils/private/X11
OBJDIR = $(BASEDIR)/$(MACHINETYPE)
SRCDIR = $(BASEDIR)/external

CFLAGS = -c -D$(MACHINETYPE) -O -g


textfieldadds = $(OBJDIR)/textfieldadds.o

$(textfieldadds): $(SRCDIR)/textfieldadds.c
	gcc $(CFLAGS) $(SRCDIR)/textfieldadds.c -o $(textfieldadds)
