generated: programs.html interface

interface: always
	cd interface; ./makeHTML

programs.html: always
	../bin/make_program_list.perl -n basiclib-3.html -p index.html -t 'Basic Libraries' *-?.html *-??.html > programs.html

tags:
	etags demo/copyexpand interface/makeRTF interface/headers.perl

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

always:
	@echo ""
