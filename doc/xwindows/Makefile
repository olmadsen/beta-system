generated: programs.html interface

interface: always
	cd interface; make

programs.html: always
	../bin/make_program_list.perl -n xwindows-3.html -p legal.html -t 'X Libraries - Reference Manual' *-?.html *-??.html > programs.html

tags:
	etags *.html

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*/*.html

always:
	@echo ""
