BASEDIR = $(BETALIB)guienv/fix/private/X11
OBJDIR = $(BASEDIR)/$(MACHINETYPE)
SRCDIR = $(BASEDIR)/external

CFLAGS = -c -D$(MACHINETYPE) -O -I/usr/include -I$(MOTIFINC) -g

BUTTON = $(OBJDIR)/Button.o
ICONBUTTON = $(OBJDIR)/IconButton.o
TOGGLEBUTTON = $(OBJDIR)/ToggleButton.o
GUIENV = $(OBJDIR)/guienv_unix.o
CANVAS = $(OBJDIR)/Canvas.o

OBJECTS = $(BUTTON) $(ICONBUTTON) $(TOGGLEBUTTON) $(GUIENV) $(CANVAS)

all: button iconbutton togglebutton guienv canvas

button: $(BUTTON)

iconbutton: $(ICONBUTTON)

togglebutton: $(TOGGLEBUTTON)

guienv: $(GUIENV)

canvas: $(CANVAS)

$(BUTTON): $(SRCDIR)/Button.c
	gcc $(CFLAGS) $(SRCDIR)/Button.c -o $(BUTTON)

$(ICONBUTTON): $(SRCDIR)/IconButton.c
	gcc $(CFLAGS) $(SRCDIR)/IconButton.c -o $(ICONBUTTON)

$(TOGGLEBUTTON): $(SRCDIR)/ToggleButton.c
	gcc $(CFLAGS) $(SRCDIR)/ToggleButton.c -o $(TOGGLEBUTTON)

$(GUIENV): $(SRCDIR)/guienv_unix.c
	gcc $(CFLAGS) $(SRCDIR)/guienv_unix.c -o $(GUIENV)

$(CANVAS): $(SRCDIR)/Canvas.c
	gcc $(CFLAGS) $(SRCDIR)/Canvas.c -o $(CANVAS)
