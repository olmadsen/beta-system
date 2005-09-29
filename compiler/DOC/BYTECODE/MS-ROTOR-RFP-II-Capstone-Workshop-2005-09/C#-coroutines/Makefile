cs: csc
	clix Merger.exe
csc:
	csc -nologo -t:library Coroutine.cs
	csc -nologo -nowarn:0164 -t:exe -r:Coroutine.dll Merger.cs

clean:
	rm -f *~ *.dll *.exe

