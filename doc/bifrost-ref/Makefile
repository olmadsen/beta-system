generated: figures.html interface

interface: always
	cd interface; ./makeHTML

figures.html: always
	../bin/make_figure_list.perl -n bifrost-ref-3.html -p index.html -t 'Bifrost Graphics System' *-?.html *-??.html > figures.html

demo: always
	cd demo; ./copyexpand 

eps:
	@cd figures; for f in *.ps; do freja2eps $$f; done

tags:
	etags demo/copyexpand interface/makeRTF interface/headers.perl

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

always:
	@echo ""
