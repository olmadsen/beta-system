doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p mjolner-tut.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc mjolner-tut.book

tags:
	etags src/*.html ../mjolner-guided-tour/src/*.html ../sif-tut/src/*.html ../freja-tut/src/*.html ../frigg-tut/src/*.html ../valhalla-tut/src/*.html

clean:
	-/bin/rm -f *~ src/*~ ../mjolner-guided-tour/src/*~ ../sif-tut/src/*~ ../freja-tut/src/*~ ../frigg-tut/src/*~ ../valhalla-tut/src/*~

distclean: clean
	-/bin/rm -f *.html *.pdf
	if [ -d interface ]; then /bin/rm -rf interface; fi

always:
	@echo ""
