generated: programs.html interface pdf

interface: always
	@echo Generating interface descriptions
	@cd interface; ./makeHTML

programs.html: always
	@echo Generating programs.html
	@../bin/make_program_list.perl -n basiclib-3.html -p index.html -t 'Basic Libraries' *-?.html *-??.html > programs.html

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
