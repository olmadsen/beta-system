all: cat whatis

cat:
	@echo Formating pages
	catman -n -M $(BETALIB)/man 1

whatis:
	@echo Building whatis
	catman -w -M $(BETALIB)/man 1
