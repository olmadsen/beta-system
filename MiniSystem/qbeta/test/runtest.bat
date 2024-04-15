@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/MiniSystem/qbeta/test
echo %BL%

rm A_trace.txt B_trace.txt C_trace.txt trace.txt

cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun2 > B_list 
cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun3 > C_list

C:/beta/r5.5/MiniSystem/qbeta/test/testrun1


echo "Done"

set /P V="wait:"
echo V
cat A_trace.txt B_trace.txt C_trace.txt >trace.txt
