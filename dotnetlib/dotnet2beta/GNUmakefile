all: DotnetConverter.exe

DotnetConverter.exe: DotnetConverter.cs BetaOutput.dll
	csc -nologo -t:exe -r:System.dll -r:BetaOutput.dll $<

%.dll:: %.cs
	csc -nologo -t:library $<

clean:
	rm -f *~ *.dll *.exe 
	rm -rf obj

