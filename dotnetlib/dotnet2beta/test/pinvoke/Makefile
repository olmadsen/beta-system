cs:
	cl -Fehellolib.dll -Zi -LD hellolib.c -link -DEF:hellolib.def
	csc -t:library hellowrapper.cs
	csc -t:exe -r:hellowrapper.dll helloworld.cs
	helloworld.exe

clean:
	rm -f *~ *.dll *.astL *.a2s *.exp *.ilk *.obj *.config.new *.exe *.stackdump *.pdb *.dump
	rm -rf clr jvm
