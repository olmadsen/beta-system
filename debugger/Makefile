BETA	= beta

try: always
	$(BETA) -q -r -o xvalhalla valhalla

tags:
	etags *.bet private/*.bet UI/*.bet UI/private/*.bet utils/*.bet private/external/*.c private/external/*.make

clean:
	/bin/rm -f \
 *..dbc \
 doc/*~ \
 XRESOURCES/*~ \
 private/external/*~ \
 *.dump *~ *.lst private/*.dump private/*.lst private/*~ \
 UI/*.dump UI/*~ UI/*.lst UI/private/*.dump UI/private/*.lst UI/private/*~ \
 utils/*.dump utils/*~ utils/*.lst
	sh -c 'if [ -d betarun/sun4s ]; then cd betarun/sun4s; make clean; fi'

always:
	