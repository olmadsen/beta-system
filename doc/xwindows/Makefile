generated: programs.html interface pdf

interface: always
	cd interface; make

programs.html: always
	../bin/make_program_list.perl -n xwindows-3.html -p legal.html -t 'X Libraries - Reference Manual' *-?.html *-??.html > programs.html

pdf:
	../bin/html2pdf.perl

tags:
	etags *.html

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*/*.html

always:
	@echo ""
