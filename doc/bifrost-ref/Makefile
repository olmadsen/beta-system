doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -s -p bifrost-ref.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc -s bifrost-ref.book

tags:
	etags src/*.html

clean:
	-/bin/rm -f *~ src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interface ]; then /bin/rm -rf interface; fi

always:
	@echo ""
