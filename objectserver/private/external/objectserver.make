include /users/beta/objectserver/v2.1/private/external/objectserver.common.make

make: $(odir)runAlloc_$(MACHINETYPE).o

$(odir)runAlloc_$(MACHINETYPE).o: $(extdir)runAlloc_$(MACHINETYPE).s
	as -o $(odir)runAlloc_$(MACHINETYPE).o $(extdir)runAlloc_$(MACHINETYPE).s

