@echo off

echo bobsit version 1.6

if "%1"=="-b" goto isboot
set boot=0
if "%1"=="" goto missing
if not "%2"=="" goto missing
set grammar=%1
:normal
echo normal exbobs
exbobs < %grammar%-parser.bobs
goto start

:isboot
set boot=1
if "%2"=="" goto missing
echo 3
if not "%3"=="" goto missing
echo 4
set grammar=%2
echo 5
if not "%grammar%"=="metagrammar" goto normal
echo booting metagrammar with bobsit
%BETALIB%\boot\bin\nti_%MIASDK%\exbobs < %BETALIB%\boot\grammars\metagrammar\%grammar%-parser.bobs
echo 6

:start
if not exist bobslist goto KEEPGOING
if exist %grammar%-parser.lst del %grammar%-parser.lst
rename bobslist %grammar%-parser.lst
:KEEPGOING

echo "End-of-BOBS"
if not exist tables goto gramerrors

echo Creating tables (tabc version 1.6)
if "%boot%"=="1" goto boottabc
	tabc tables %grammar%-parser %grammar%
	goto pasttabc
:boottabc
	echo ..boot...tabc tables %grammar%-parser
	%BETALIB%\boot\bin\nti_%MIASDK%\tabc tables %grammar%-parser %grammar%
:pasttabc

goto done

:missing
echo "Usage: bobsit <grammar-name>"
goto done

:gramerrors
echo ERRORS IN GRAMMAR
echo Look at %1-parser.lst
goto done

:done
rem Done




