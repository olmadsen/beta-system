TSTFILES = \
tst.bet \
tstarith.bet \
tstbigobject.bet \
tstblock.bet \
tstbool.bet \
tstbreak.bet \
tstbreakbody.bet \
tstcom.bet \
tstcomp.bet \
tstcompref.bet \
tstcomprem2.bet \
tstcontrol.bet \
tstcproc.bet \
tstdobody.bet \
tstdopart.bet \
tstdopartbody.bet \
tstenv.bet \
tstenvbody.bet \
tstgeneralrep.bet \
tstholder.bet \
tstinlinenx.bet \
tstint8.bet \
tstlib.bet \
tstlibbody.bet \
tstlvra.bet \
tstmainp.bet \
tstmainpbody.bet \
tstnewprim.bet \
tstnx.bet \
tstnx2.bet \
tstnx3.bet \
tstnxoff.bet \
tstnxoff2.bet \
tstnxoff3.bet \
tstoldprim.bet \
tstorigin.bet \
tstprogram.bet \
tstreal.bet \
tstref.bet \
tstrefrep.bet \
tstrefreplarge.bet \
tstrelop.bet \
tstrep.bet \
tstsystemenv.bet \
tstthis.bet \
tstthis2.bet \
tstvarptn.bet \
tstvirt.bet \
tstvirt2.bet

tst: $(TSTFILES)
	beta -qw tst
check: tst
	tst | grep -v 'abcdefghijklmnopqrstuvwxyz0123456789'

tags:
	etags *.bet misc/*.bet tstdump/*.bet *.make *.c
clean:
	@echo Cleaning TST
	-@/bin/rm -f *~ *.ast *.astL *.lst *.dump */*~ */*.ast */*.astL */*.lst */*.o */*.s */*..job */*/*.o */*/*.s */*/*..job tstdump/tstdump?? tstdump/*.out tst misc/tstgc misc/tstcb misc/tstqua misc/tstrepgc
	-@/bin/rm -f *.dll *.exe *.pdb *.config