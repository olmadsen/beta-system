OBJDIR       = ../$(MACHINETYPE)
CFLAGS       = -c -D$(MACHINETYPE) -I/usr/include -I$(MOTIFINC)

BUTTON       = $(OBJDIR)/Button.o
ICONBUTTON   = $(OBJDIR)/IconButton.o
TOGGLEBUTTON = $(OBJDIR)/ToggleButton.o
GUIENV       = $(OBJDIR)/guienv_unix.o
CANVAS       = $(OBJDIR)/Canvas.o


all: $(BUTTON) $(ICONBUTTON) $(TOGGLEBUTTON) $(GUIENV) $(CANVAS)

$(BUTTON): Button.c
	$(CC) $(CFLAGS) Button.c -o $(BUTTON)

$(ICONBUTTON): IconButton.c
	$(CC) $(CFLAGS) IconButton.c -o $(ICONBUTTON)

$(TOGGLEBUTTON): ToggleButton.c
	$(CC) $(CFLAGS) ToggleButton.c -o $(TOGGLEBUTTON)

$(GUIENV): guienv_unix.c
	$(CC) $(CFLAGS) guienv_unix.c -o $(GUIENV)

$(CANVAS): Canvas.c
	$(CC) $(CFLAGS) Canvas.c -o $(CANVAS)
