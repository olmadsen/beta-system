all: dist link-check

# Re-generate all the generated files in the various manuals.
dist:
	@perl -s build

# Re-generate all the generated files except PDF in the various manuals.
doc:
	@perl -s build -p

link-check:
	@echo Checking all links from index.html
	cd admin/errors; /bin/rm -f *.*; touch linklint.html
	perl bin/linklint_2.1/linklint -net -error -xref -doc admin/errors -quiet -orphan -htmlonly -limit 2000 -ignore /contents.html -root . -index index.html  /@ 
	@echo See file admin/errors/linklint.html for a survey of errors.

make-check:
	@echo Checking Makefiles
	sh -c 'for d in *; do if [ -f $$d/Makefile ] ; then echo $$d; cd $$d; make -n; cd ..; fi; done'


up: update

update:
	cvs update -dP

# Tags: Only include html files that are not generated
tags:
	etags \
*.html \
*/src/*.html

# Remove garbage in top directory
topclean:
	/bin/rm -f *~ javascript/*~ style/*~ 

# Remove garbage
clean: topclean
	@env -i PATH=$$PATH BETALIB=$$BETALIB QUIET=1 sh -c 'for d in *; do if [ -f $$d/Makefile ] ; then /usr/xpg4/bin/grep -q clean: $$d/Makefile; status=$$?; if [ $$status -eq 0 ] ; then cd $$d; echo ""; echo "---$$d---"; make clean; cd ..; fi; fi; done'


# Remove all generated files
distclean: topclean
	@env -i PATH=$$PATH BETALIB=$$BETALIB QUIET=1 sh -c 'for d in *; do if [ -f $$d/Makefile ] ; then /usr/xpg4/bin/grep -q distclean: $$d/Makefile; status=$$?; if [ $$status -eq 0 ] ; then cd $$d; echo ""; echo "---$$d---"; make distclean; cd ..; fi; fi; done'

