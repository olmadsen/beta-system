AS=masm386
AFLAGS=/t /Ml /Zd

CC=cl
CFLAGS=/nologo /O2 /Zd /DWIN32 /D$(MACHINETYPE) /D$(MACHINETYPE)_$(SDK) /Zp4 /c

MACHDIR=$(BASEDIR)\$(MACHINETYPE)
OBJDIR=$(MACHDIR)\$(SDK)
BETARUNDIR=$(BETALIB)\betarun\v2.9\$(MACHINETYPE)

.SUFFIXES: .obj .asm .c

{$(SRCDIR)}.asm{$(OBJDIR)}.obj:
    $(AS) $(AFLAGS) $<,$@;

{$(SRCDIR)}.c{$(OBJDIR)}.obj:
    $(CC) $(CFLAGS) /Fo$@ $<

# special case for objectserver
{$(BETARUNDIR)\C}.c{$(OBJDIR)}.obj:
    $(CC) $(CFLAGS) /Fo$@ $<

all: $(MACHDIR) $(OBJDIR) $(MAKEOBJS)

$(MACHDIR) $(OBJDIR):
	if not exist $@\nul mkdir $@
