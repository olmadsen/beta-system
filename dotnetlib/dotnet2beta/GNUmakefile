dotnet2beta.exe: DotnetConverter.cs BetaOutput.dll
	csc -nologo -debug:full -t:exe -out:dotnet2beta.exe -r:System.dll -r:BetaOutput.dll $<

%.dll:: %.cs
	csc -nologo -debug:full -t:library $<

clean:
	rm -f *~ *.dll *.exe *.pdb *.suo *.netmodule
	rm -rf obj

