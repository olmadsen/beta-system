# Usages:
#
#	make
#	make pdf
#	  Both generates bytecode.pdf
#
#	make thumbs
#	  Generate bytecode.pdf augmented with PDF thumbnails
#
#	make acro
#	  Generate bytecode.pdf with thumbnails and open acroread
#
#	make clean
#	  Remove all generated files except bytecode.pdf
#

pdf: bytecode.pdf

thumbs: bytecode.pdf
	thumbpdf bytecode.pdf
	pdflatex bytecode.tex

acro: thumbs
	@echo Quit acroread to get prompt back...
	acroread -geometry 1000x1000 bytecode.pdf

bytecode.pdf: always
	pdflatex bytecode.tex
	pdflatex bytecode.tex

always:

clean:
	/bin/rm -f *.dvi *.aux *.log *.out *.tpt *~ 

