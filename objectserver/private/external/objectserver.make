include objectserver.common.make

make: ../$(MACHINETYPE)/runAlloc_$(MACHINETYPE).o

../$(MACHINETYPE)/runAlloc_$(MACHINETYPE).o: runAlloc_$(MACHINETYPE).s
	as -o ../$(MACHINETYPE)/runAlloc_$(MACHINETYPE).o runAlloc_$(MACHINETYPE).s

