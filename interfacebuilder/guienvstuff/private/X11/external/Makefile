BASEDIR = $(BETALIB)interfacebuilder/v1.0/guienvadds/private/X11
OBJDIR = $(BASEDIR)/$(MACHINETYPE)
SRCDIR = $(BASEDIR)/external

CFLAGS = -c -D$(MACHINETYPE) -O -g


textfieldadds = $(OBJDIR)/textfieldadds.o

$(textfieldadds): $(SRCDIR)/textfieldadds.c
	gcc $(CFLAGS) $(SRCDIR)/textfieldadds.c -o $(textfieldadds)
