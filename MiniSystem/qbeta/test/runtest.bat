@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/MiniSystem/qbeta/test
echo %BL%

echo %1 %2 %3

rm -v A_trace.txt B_trace.txt C_trace.txt trace.txt

cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun3 %1 %2 
cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun2 %1 %2
cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun4 %1 %2

C:/beta/r5.5/MiniSystem/qbeta/test/testrun1 %1 %2


echo "Done"

set /P V="wait:"
cat A_trace.txt B_trace.txt C_trace.txt D_trace.txt>trace.txt
ls -lt

