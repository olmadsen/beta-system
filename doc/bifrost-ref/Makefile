interface: always
	cd interface; ./makeHTML

demo: always
	cd demo; ./copyexpand 

eps:
	@cd figures; for f in *.ps; do freja2eps $$f; done

tags:
	etags demo/copyexpand interface/makeRTF interface/headers.perl

clean:
	-/bin/rm -f *~ demo/*.bet interface/*~ figures/*~ 

always:
	@echo ""
