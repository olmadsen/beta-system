rem Windows cmd.exe BETA.Net/BETA.Java setup
@echo off
set BETALIB=%CD%
set PATH=%CD%\bin;%PATH%
cd examples
echo BETALIB and PATH set. 
echo Now call make_clean.bat and then use jbeta/nbeta for compilation.
