OBJDIR = ../$(MACHINETYPE)
CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC)

$(OBJDIR)/getdesignglobalapplw.o: getdesignglobalapplw.c
	$(CC) $(CFLAGS) getdesignglobalapplw.c -o $(OBJDIR)/getdesignglobalapplw.o
