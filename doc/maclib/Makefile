generated: interface

interface: always
	@echo Generating interface descriptions
	@cd interface; ./makeHTML

tags:
	etags demo/copyexpand interface/makeRTF interface/headers.perl

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

check:
	weblint -x Netscape -x Microsoft -d empty-container interface/*.html

always:
	@echo ""
