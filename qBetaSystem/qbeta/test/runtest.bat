@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/qBetaSystem/qbeta/test
echo %BL%

rm -v A_trace.txt B_trace.txt C_trace.txt D_trace.txt E_trace.txt trace.txt

cygstart C:/beta/r5.5/qBetaSystem/qbeta/test/testrun3
cygstart C:/beta/r5.5/qBetaSystem/qbeta/test/testrun2
cygstart C:/beta/r5.5/qBetaSystem/qbeta/test/testrun4
cygstart C:/beta/r5.5/qBetaSystem/qbeta/test/testrun5

C:/beta/r5.5/qBetaSystem/qbeta/test/testrun1


echo "Done"

set /P V="wait:"
cat A_trace.txt B_trace.txt C_trace.txt D_trace.txt E_trace.txt>trace.txt
ls -lt *.txt

