AS=ml
AFLAGS=/w /nologo /coff /Cp /c

CC=cl
CFLAGS=/nologo /O2 /Zd /DWIN32 /D$(MACHINETYPE) /D$(MACHINETYPE)_$(SDK) /Zp4 /c

MACHDIR=$(BASEDIR)\$(MACHINETYPE)
OBJDIR=$(MACHDIR)\$(SDK)

.SUFFIXES: .obj .asm .c

{$(SRCDIR)}.asm{$(OBJDIR)}.obj:
    $(AS) $(AFLAGS) /Fo$@ /Ta$<

{$(SRCDIR)}.c{$(OBJDIR)}.obj:
    $(CC) $(CFLAGS) /Fo$@ $<

all: $(MACHDIR) $(OBJDIR) $(MAKEOBJS)

$(MACHDIR) $(OBJDIR):
	if not exist $@\nul mkdir $@
