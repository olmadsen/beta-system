include objectserver.common.make

make: $(odir)runAlloc_$(MACHINETYPE).o

$(odir)runAlloc_$(MACHINETYPE).o: $(extdir)runAlloc_$(MACHINETYPE).s
	as -o $(odir)runAlloc_$(MACHINETYPE).o $(extdir)runAlloc_$(MACHINETYPE).s

