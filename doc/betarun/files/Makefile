all:
	beta -qw runtimeerr
	-runtimeerr
	sed -e "s%/users/datpete/public_html/doc/betarun/files%/usr/smith%g" < runtimeerr.dump > dump.bet
	../../bin/beta2html.perl -n fisk -p fisk -t dump dump.bet

clean:
	/bin/rm -f *.dump dump.bet dump.html runtimeerr
