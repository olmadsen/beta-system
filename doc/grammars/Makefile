MAKEHTML = ../bin/gram2frames.perl

all:	beta idl metagrammar prettyprint property
	@echo Done.

beta:
	@echo Generating beta.html
	@$(MAKEHTML) ${BETALIB}/grammars/beta/beta-meta.gram
idl:
	@echo Generating idl.html
	@$(MAKEHTML) ${BETALIB}/grammars/idl/idl-meta.gram
metagrammar:
	@echo Generating metagrammar.html
	@$(MAKEHTML) ${BETALIB}/grammars/metagram/metagrammar-meta.gram
prettyprint:
	@echo Generating prettyprint.html
	@$(MAKEHTML) ${BETALIB}/grammars/pretty/prettyprint-meta.gram
property:
	@echo Generating property.html
	@$(MAKEHTML) ${BETALIB}/grammars/property/property-meta.gram

tags:
	@echo There is nothing to tag here.
