doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p mjolner-ref.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc mjolner-ref.book

tags:
	etags ../sif/src/*.html ../freja/src/*.html ../frigg/src/*.html ../valhalla/src/*.html

clean:
	-/bin/rm -f *~ ../sif/src/*~ ../freja/src/*~ ../frigg/src/*~ ../valhalla/src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf

always:
	@echo ""
