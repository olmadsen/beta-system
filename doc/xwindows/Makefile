doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p xwindows.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc xwindows.book

tags:
	etags src/*.html

clean:
	-/bin/rm -f *~ src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interfaces ]; then /bin/rm -rf interfaces; fi

always:
	@echo ""
