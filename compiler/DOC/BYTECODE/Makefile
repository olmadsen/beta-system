view: pdf
	@echo Quit acroread to get prompt back...
	acroread -geometry 1000x1000 bytecode.pdf

pdf: bytecode.pdf

bytecode.pdf: always
	pdflatex bytecode.tex
	pdflatex bytecode.tex
	thumbpdf bytecode.pdf
	pdflatex bytecode.tex

always:

clean:
	/bin/rm -f *.dvi *.aux *.log *.out *~ 

