OBJDIR = ../$(MACHINETYPE)

CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC) -O -g


defaultfont = $(OBJDIR)/defaultfont.o

$(defaultfont): defaultfont.c
	gcc $(CFLAGS) defaultfont.c -o $(defaultfont)
