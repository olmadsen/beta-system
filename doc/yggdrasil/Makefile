generated: interface pdf

interface: always
	cd interface; ./makeHTML

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

pdf:
	../bin/html2pdf.perl

always:
	@echo ""
