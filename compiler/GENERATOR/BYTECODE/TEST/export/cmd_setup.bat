rem Windows cmd.exe BETA.Net/BETA.Java setup
@echo off
set JAVAHOME="C:\Program Files\Java"
set JNIDIR="win32"
set DYNEXTENSION="dll"
echo JAVA specific variables set: JAVAHOME, JNIDIR, DYNEXTENSION. 
echo JAVAHOME=%JAVAHOME% assumed - fix script if this is not correct.
set BETALIB=%CD%
set PATH=%CD%\bin;%JAVAHOME%\bin;%PATH%
cd examples
echo BETALIB and PATH set. 
echo Now start using jbeta/nbeta for compilation.
