generated: figures.html interface pdf

interface: always
	@echo Generating interface descriptions
	@cd interface; ./makeHTML
	@cd interface-utils; ./makeHTML
	@cd interface-multimedia; ./makeHTML
	@cd interface-openGL; ./makeHTML

tags:
	etags demo/copyexpand interface/makeRTF interface/headers.perl

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

pdf:
	@../bin/html2pdf.perl

always:
	@echo ""
