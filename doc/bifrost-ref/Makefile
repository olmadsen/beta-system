generated: figures.html interface pdf

interface: always
	cd interface; ./makeHTML

figures.html: always
	../bin/make_figure_list.perl -n bifrost-ref-3.html -p index.html -t 'Bifrost Graphics System' *-?.html *-??.html > figures.html

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

pdf:
	../bin/html2pdf.perl

always:
	@echo ""
