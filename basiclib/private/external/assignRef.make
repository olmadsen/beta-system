BASEDIR = $(BETALIB)/basiclib/v1.5/private

make: $(BASEDIR)/$(MACHINETYPE)/assignRef.o

$(BASEDIR)/$(MACHINETYPE)/assignRef.o: $(BASEDIR)/external/assignRef.c
	gcc -O -c -o $(BASEDIR)/$(MACHINETYPE)/assignRef.o $(BASEDIR)/external/assignRef.c

$(BASEDIR)/$(MACHINETYPE):
	mkdir $(BASEDIR)/$(MACHINETYPE)

