java: javac
	java  -classpath "$(BETALIB)/basiclib/jvm;$(BETALIB)/basiclib/private/jvm;." Merger
javac:
	javac -classpath "$(BETALIB)/basiclib/jvm;$(BETALIB)/basiclib/private/jvm;." Merger.java

cs: csc
	Merger.exe
csc:
	csc -nologo -t:library -r:"$(BETALIB)/basiclib/clr/betaenv.dll,$(BETALIB)/basiclib/private/clr/Component.dll" Coroutine.cs
	csc -nologo -nowarn:0164 -t:exe -r:"Coroutine.dll,$(BETALIB)/basiclib/clr/betaenv.dll,$(BETALIB)/basiclib/private/clr/Component.dll" Merger.cs
	mkdir -p Merger
	cp Coroutine.dll Merger
	cp $(BETALIB)/basiclib/clr/betaenv.dll Merger
	cp $(BETALIB)/basiclib/private/clr/Component.dll Merger

clean:
	rm -f *.class *~ *.dll *.exe
	rm -rf Merger


