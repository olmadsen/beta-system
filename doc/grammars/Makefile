MAKEHTML = ../bin/gram2html.perl

all:	beta idl metagrammar prettyprint property
	@echo Done.

beta:
	$(MAKEHTML) ${BETALIB}/grammars/beta/beta-meta.gram > beta.html
idl:
	$(MAKEHTML) ${BETALIB}/grammars/idl/idl-meta.gram > idl.html
metagrammar:
	$(MAKEHTML) ${BETALIB}/grammars/metagram/metagrammar-meta.gram > metagrammar.html
prettyprint:
	$(MAKEHTML) ${BETALIB}/grammars/pretty/prettyprint-meta.gram > prettyprint.html
property:
	$(MAKEHTML) ${BETALIB}/grammars/property/property-meta.gram > property.html
