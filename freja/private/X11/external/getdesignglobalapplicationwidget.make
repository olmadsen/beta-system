OBJDIR = ../$(MACHINETYPE)
CFLAGS = -c -D$(MACHINETYPE) -I$(MOTIFINC)

$(OBJDIR)/getdesignglobalapplicationwidget.o: getdesignglobalapplicationwidget.c
	$(CC) $(CFLAGS) getdesignglobalapplicationwidget.c -o $(OBJDIR)/getdesignglobalapplicationwidget.o
