generated: appendix pdf

appendix:
	cp $(BETALIB)/bifrost/tutorial/subway7.bet .
	@../bin/beta2html.perl -n snapshot.html -p readings.html -t 'Appendix A. The Final Program' subway7.bet
	mv subway7.html final.html
	rm subway7.bet

pdf:
	../bin/html2pdf.perl
