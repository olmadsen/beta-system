# Makefile for the test program and the my_getch()
# routine
#
# written by R. Vankemmel
#
# Note: depending on your machine you must select the 
#       CC entry accordingly. Sorry for this kludge, but
#       I need the ANSI C compiler and most vendor supplied
#       C-compilers need flags for the ANSI mode.
#
#----------------------------------------------------
# compiler flags:
#CC	= gcc
# targets:
TEST =	./test

CCOBJ=	my_getch.o my_gets.o mystrings.o

# headers 
HEADER=	sysdefs.h

all:	$(CCOBJ)

$(TEST): $(CCOBJ) test.o
	@echo "Loading program $(TEST)"
	$(CC) $(CCOBJ) test.o -o $(TEST)
	@echo "Done...."

clean: 
	@echo "Cleaning up this directory"
	@/bin/rm -f *.o $(TEST)
	@echo "Done......."

# header file dependencies:
$(CCOBJ) : $(HEADER)

# source file dependencies:
.c.o:
	$(CC) $*.c -c

# ---------------------------------------------------------------------------
