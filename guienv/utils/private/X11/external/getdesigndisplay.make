OBJDIR = ../$(MACHINETYPE)

CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC) -O -g


getdesigndisplay = $(OBJDIR)/getdesigndisplay.o

$(getdesigndisplay): getdesigndisplay.c
	gcc $(CFLAGS) getdesigndisplay.c -o $(getdesigndisplay)
