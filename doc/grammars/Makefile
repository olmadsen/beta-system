MAKEHTML = ../bin/gram2html.perl -v

all:	beta idl metagrammar prettyprint property
	@echo Done.

beta:
	$(MAKEHTML) ${BETALIB}/grammars/beta/beta-meta.gram
idl:
	$(MAKEHTML) ${BETALIB}/grammars/idl/idl-meta.gram
metagrammar:
	$(MAKEHTML) ${BETALIB}/grammars/metagram/metagrammar-meta.gram
prettyprint:
	$(MAKEHTML) ${BETALIB}/grammars/pretty/prettyprint-meta.gram
property:
	$(MAKEHTML) ${BETALIB}/grammars/property/property-meta.gram
