generated: interface pdf

interface: always
	@echo Generating interface descriptions
	@cd interface; ./makeHTML
	@cd interface-utils; ./makeHTML
	@cd interface-multimedia; ./makeHTML
	@cd interface-openGL; ./makeHTML

pdf:
	@../bin/html2pdf.perl

always:
	@echo ""
