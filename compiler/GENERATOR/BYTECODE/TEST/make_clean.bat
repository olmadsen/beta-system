del /f /q *~ *.dll *.pdb *.exe *.out *.lst *.class *.jar *.astL *.ast *.a2s *.dump *.diff >NUL 2>1
del /f /q *.exe.config.new *.suo *.sln >NUL 2>1
del /s /f /q clr jvm sun4s linux nti_ms nti_gnu >NUL 2>1
del /f /q *.manifest >NUL 2>1
del /f /q googleapi\dotnet\GoogleSearchService.dll >NUL 2>1
del /f /q googleapi\dotnet\GoogleSearchService.pdb >NUL 2>1
del /s /f /q amazon\dotnet >NUL 2>1

jbeta -w tstenv >NUL
jbeta -w betaenv >NUL
nbeta -w tstenv >NUL
nbeta -w betaenv >NUL 
del /f /q jvm\String.class >NUL 2>1
cls

