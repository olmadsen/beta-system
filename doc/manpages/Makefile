doc: buildsrcverbose
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p manpages.book

buildsrcverbose:
	@perl -s buildsrc -v

dist: buildsrcquiet
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc manpages.book

buildsrcquiet:
	@perl -s buildsrc

tags:
	@echo There is nothing to tag here.

clean:
	-/bin/rm -f *~ 

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d src ]; then /bin/rm -rf src; fi

always:
	@echo ""
