@echo off

if "%1"=="-b" goto boot

if "%1"=="" goto missing
if not "%2"=="" goto missing
echo generator
call gen %1
echo bobsit version 1.6
call exbobs < %1-parser.bobs
if not exist bobslist goto KEEPGOING
if exist %1-parser.lst del %1-parser.lst
rename bobslist %1-parser.lst
:KEEPGOING

echo "End-of-BOBS"
if not exist tables goto gramerrors

echo Creating tables (tabc version 1.6)
call tabc tables %1-parser %1

echo makepretty
call makepretty %1

echo morepretty
call morepretty %1

goto done

:boot

echo Booting %grammar% with dogram
if "%2"=="" goto missing
if not "%3"=="" goto missing
echo generator
call %BETALIB%\boot\bin\nti_%MIASDK%\gen %2
echo bobsit version 1.6
call %BETALIB%\boot\bin\nti_%MIASDK%\exbobs < %2-parser.bobs
if not exist bobslist goto KEEPGOING
if exist %2-parser.lst del %2-parser.lst
rename bobslist %2-parser.lst
:KEEPGOING

echo "End-of-BOBS"
if not exist tables goto gramerrors

echo Creating tables (tabc version 1.6)
call %BETALIB%\boot\bin\nti_%MIASDK%\tabc tables %2-parser %2

goto done

:missing
echo "Usage: dogram <grammar-name>"
goto done

:gramerrors
echo ERRORS IN GRAMMAR
echo Look at %1-parser.lst
goto done

:done
rem Done




