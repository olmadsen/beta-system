cs:
	mkdir -p clr/helloworld
	cl -Feclr/helloworld/hellolib.dll -Zi -LD hellolib.c -link -DEF:hellolib.def
	csc -t:library -out:clr/helloworld/hellowrapper.dll hellowrapper.cs
	csc -t:exe -r:clr/helloworld/hellowrapper.dll helloworld.cs
	helloworld.exe

clean:
	rm -f *~ *.dll *.astL *.a2s *.exp *.ilk *.obj *.config.new *.exe *.stackdump *.pdb *.dump
	rm -rf clr jvm
