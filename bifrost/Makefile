BETA= beta4.5
BETASW= 19 18
#BETAOPTS= -m uranus
BETAOPTS= 
.IGNORE:
.SILENT:

SHELL=/bin/sh


beta:	
	mv -f LOG LOG.o
	echo Switches: $(BETASW) 32
	$(BETA) -r -s $(BETASW) 32 0 $(BETAOPTS) 2>&1 | tee LOG

lst:
	mv -f LOG LOG.o
	echo Switches: $(BETASW)
	$(BETA) -r -s $(BETASW) 0 $(BETAOPTS) 2>&1 | tee LOG

check:	
	mv -f LOG LOG.o
	echo Switches: $(BETASW) 1 191 192 193
	$(BETA) -r -s $(BETASW)  1 191 192 193 0 $(BETAOPTS) 2>&1 | tee LOG

mac:
	echo Switches: $(BETASW)
	$(BETA) -t mac -r -s $(BETASW) 0 $(BETAOPTS) 2>&1 | tee MACLOG

touch:
	touch *.bet Impl/*.bet Predefined/*.bet Rubber/*.bet Mac/*.bet X11/*.bet gungne/*.bet bdraw/*.bet

time:
	mv -f TIMELOG TIMELOG.o
	/bin/time $(BETA) -s $(BETASW) 4 0 bdraw/bdraw 2>&1 | tee TIMELOG

bifrost:
	mv -f LOG LOG.o
	echo Compiling bifrost...
	$(BETA) -s $(BETASW) 0 $(BETAOPTS) bifrost.bet 2>&1 | tee LOG

all:	bdraw/bdraw

tags:
	etags *.bet private/Impl/*.bet private/Predefined/*.bet private/Rubber/*.bet private/X11/*.bet bdraw/*.bet demo/*.bet tutorial/*.bet design/*.bet

gtags:
	csh -c 'etags --output=GUIENV_TAGS /users/beta/guienv/v1.2/{*.bet,*/*.bet,*/*/*.bet}'

dopartlist:
	grep -h 'dopart --' *.bet private/Impl/*.bet private/Predefined/*.bet private/Rubber/*.bet private/X11/*.bet private/Xt/*.bet bdraw/*.bet demo/*.bet tutorial/*.bet | sort
allways: ;

interface: allways
	cd /users/beta/miadoc/bifrost-ref/v0.2/scripts; ./makeRTF

codesize: allways
	private/scripts/codesize.sh

clean:
	echo Removing files:
	find . \( -name '*.lst' -o -name '*~' -o -name '*..job' -o -name '*..s' -o -name '*.dump' \) -print -exec rm '{}' \; 

gclean:
	echo Removing files:
	find . \( -name '*.lst' -o -name '*~' -o -name '*..job' -o -name '*.group' -o -name '*..s' -o -name '*.dump' \) -print -exec rm '{}' \; 
