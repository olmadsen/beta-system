objfile = $(MACHINETYPE)/ipipe.o

all: $(objfile)

$(objfile): ipipe.c
	$(CC) $(debug) -D$(MACHINETYPE) -c ipipe.c -o $(objfile)
