doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p beta.book
	@perl -s ../bin/makedoc -v -p fragment.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc beta.book
	@perl -s ../bin/makedoc fragment.book

tags:
	etags src/*.html

clean:
	-/bin/rm -f *~ src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interfaces ]; then /bin/rm -rf interfaces; fi

always:
	@echo ""
