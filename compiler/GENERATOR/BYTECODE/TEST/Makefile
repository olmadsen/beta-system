clean:
	-rm -f *~ *.dll *.pdb *.exe *.bat *.out *.lst *.class *.jar *.astL *.ast *.a2s *.dump *.diff
	-rm -f *.exe.config.new *.suo *.sln
	-rm -rf dotnet javabc sun4s linux nti_ms nti_gnu
	-rm -f *.manifest
	-rm -f googleapi/dotnet/GoogleSearchService.dll
	-rm -f googleapi/dotnet/GoogleSearchService.pdb
	-jbeta -w tstenv > /dev/null
	-jbeta -w betaenv > /dev/null
	-nbeta -w tstenv > /dev/null
	-nbeta -w betaenv > /dev/null
	@-rm -f javabc/String.class

