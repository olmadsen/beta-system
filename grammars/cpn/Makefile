
html:
	${BETALIB}/doc/bin/gram2html.perl -c -f cpn-meta.gram
dogram:
	dogram cpn
parse:
	parse cpn-parser.btab demo/Sender.int -doc -
tparse:
	parse cpn-parser.btab demo/Sender.int -doc - -trace
parsebig:
	parse cpn-parser.btab demo/OK409-2.int -doc -
tparsebig:
	parse cpn-parser.btab demo/OK409-2.int -doc - -trace
