doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p grammars.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc grammars.book


tags:
	@echo There is nothing to tag here.

clean:
	-/bin/rm -f *~ 

distclean: clean
	-/bin/rm -f *.html *.pdf

always:
	@echo ""
