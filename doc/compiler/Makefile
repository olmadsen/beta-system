doc: always
	@echo Generating documentation without PDF
	@perl -s ../bin/makedoc -v -p compiler.book

dist: always
	@echo Generating documentation with PDF
	@perl -s ../bin/makedoc compiler.book

tags:
	etags src/*.html files/

src/messages.html: files/MakeMsgList
	cd src; ../files/MakeMsgList

files/MakeMsgList: files/MakeMsgList.bet $(BETALIB)/betaast/semanticerrortext.bet
	beta files/MakeMsgList

files/syntaxerror.err: files/syntaxerror.bet
	-beta syntaxerror.bet>files/syntaxerror.err

clean:
	-/bin/rm -rf *~ src/*~ files/*~ files/*.ast files/*.astL files/MakeMsgList files/sun4s files/sgi files/linux files/hpux9pa files/nti_ms files/nti_gnu

distclean: clean
	-/bin/rm -f *.html *.pdf
	-/bin/rm -f src/messages.html
	-/bin/rm -f files/syntaxerror.err
	if [ -d interfaces ]; then /bin/rm -rf interfaces; fi

always: files/syntaxerror.err # src/messages.html 
	@echo ""
