BETA =	beta

all:
	$(BETA) syntaxerror 2>&1 >syntaxerror.err
	$(BETA) runtimeerr semanticerrors
	-(runtimeerr 2>&1) >runtimeerr.err
	semanticerrors > errorlst
clean:
	/bin/rm -f *~ *.ast */*..s */*.o */*..db */*..job runtimeerr
