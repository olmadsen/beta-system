#RM = echo
BETA = beta -qlw
RM= rm -rf

all:
	$(BETA) */*.bet */*/*.bet

code:
	$(BETA) --nolink */*.bet */*/*.bet

check:
	$(BETA) --nocode --nolink */*.bet */*/*.bet

clean:
	@echo removing garbage...
	@find . -follow \( -name 'run-demos.tar' -o -name 'run.out' -o -name 'run.def' -o -name '*.dbc' -o -name 'so_locations' -o -name '*.~group' -o -name '*.#group' -o -name '*.diag' -o -name '.??*.pjt' -o -name '*.~astL' -o -name '*.#astL' -o -name '*.#ast' -o -name '*.#ast' -o -name 'lst' -o -name '*.lst' -o -name '*.dump' -o -name 'core' -o -name '*~' \) -print -exec /bin/rm -f '{}' \;
	@echo removing ast and a2s files...
	@find . -follow \( -name '*.group' -o -name '*.ast' -o -name '*.astL' -o -name '*.a2s' \) -print -exec /bin/rm -f '{}' \;
	@echo removing executables...
	@find . -type f -follow -perm -111 -print -exec /bin/rm -f '{}' \;
	@echo removing code directories...
	@find . -follow -type d \( -name sgi -o -name sun4s -o -name linux -o -name hpux9pa -o -name nti \) -print -exec /bin/rm -rf '{}' \; 
	@echo cvs updating in case something was lost
	@cvs -q up

tar:
	@echo Creating run-demos.tar with all run.demos scripts
	sh -c "find . -name 'run.*' -print; echo demo-utils.perl; echo ./basiclib/systemenv/demo.txt; echo unixlib/unixfile/input" | xargs tar cvf run-demos.tar
