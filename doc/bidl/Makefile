doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p bidl.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc bidl.book

tags:
	etags src/*.html

clean:
	-/bin/rm -f *~ src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interfaces ]; then /bin/rm -rf interfaces; fi

always:
	@echo ""
