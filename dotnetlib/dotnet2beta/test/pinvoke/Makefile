cs:
	mkdir -p clr/helloworld
	cl -nologo -Feclr/helloworld/hellolib.dll -Zi -LD hellolib.c -link -DEF:hellolib.def
	csc -nologo -debug:full -t:library -out:clr/helloworld/hellowrapper.dll hellowrapper.cs
	csc -nologo -debug:full -t:exe -r:clr/helloworld/hellowrapper.dll helloworld.cs
	helloworld.exe

clean:
	rm -f *~ *.dll *.astL *.a2s *.exp *.ilk *.obj *.lib *.config.new *.exe *.stackdump *.pdb *.dump
	rm -rf clr jvm
