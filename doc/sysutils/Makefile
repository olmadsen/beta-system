doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p -d sysutils.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc sysutils.book

tags:
	etags src/*.html

clean:
	-/bin/rm -f *~ src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interface ]; then /bin/rm -rf interface; fi

always:
	@echo ""
