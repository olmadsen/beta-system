all: cat whatis

quiet: qcat qwhatis

cat:
	@perl -e 'print STDERR "Formating pages with catman\n";'
	@catman -n -M $(BETALIB)/man 1

whatis:
	@perl -e 'print STDERR "Building whatis\n";'
	@catman -w -M $(BETALIB)/man 1

qcat:
	@catman -n -M $(BETALIB)/man 1

qwhatis:
	@catman -w -M $(BETALIB)/man 1
