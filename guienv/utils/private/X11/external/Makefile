OBJDIR = ../$(MACHINETYPE)
SRCDIR = .

CFLAGS = -c -D$(MACHINETYPE) -O -g


textfieldadds = $(OBJDIR)/textfieldadds.o

$(textfieldadds): $(SRCDIR)/textfieldadds.c
	gcc $(CFLAGS) $(SRCDIR)/textfieldadds.c -o $(textfieldadds)
