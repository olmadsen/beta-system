AS=tasm32
AFLAGS=-w-res -t -m -ml -kh32768 -zd

MACHDIR=$(BASEDIR)\$(MACHINETYPE)
OBJDIR=$(MACHDIR)\$(SDK)

CC=bcc32
CFLAGS=-O2 -v -DWIN32 -D$(MACHINETYPE) -D$(MACHINETYPE)_$(SDK) -a4 -c

.SUFFIXES: .obj .asm .c

.asm.obj:
	if not exist $(MACHDIR)\nul mkdir $(MACHDIR)
	if not exist $(OBJDIR)\nul mkdir $(OBJDIR)
	$(AS) $(AFLAGS) $<,$@

.c.obj:
	if not exist $(MACHDIR)\nul mkdir $(MACHDIR)
	if not exist $(OBJDIR)\nul mkdir $(OBJDIR)
	$(CC) $(CFLAGS) -o$@ $<

all: $(MAKEOBJS)
