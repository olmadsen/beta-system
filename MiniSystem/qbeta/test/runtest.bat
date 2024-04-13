@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/MiniSystem/qbeta/test
echo %BL%

cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun2 > B_list 
cygstart C:/beta/r5.5/MiniSystem/qbeta/test/testrun3 > C_list

C:/beta/r5.5/MiniSystem/qbeta/test/testrun1
