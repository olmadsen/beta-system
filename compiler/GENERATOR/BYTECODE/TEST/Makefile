clean:
	rm -rf jvm clr linux sun4s nti_ms *.a2s *.ast *.astL *~ *.out *.run *.config.new *.lst lst *.jar *.class *.info *.dump *.log TAGS *.diff *.summary
	cd ECLIPSE; $(MAKE) clean
	$(MAKE) etags

etags:
	etags *.bet *.java *.cs
