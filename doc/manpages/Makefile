doc: buildverbose
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p manpages.book

buildverbose:
	@perl -s build -v

dist: buildquiet
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc manpages.book

buildquiet:
	@perl -s build

tags:
	@echo There is nothing to tag here.

clean:
	-/bin/rm -f *~ 

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d src ]; then /bin/rm -rf src; fi

always:
	@echo ""
