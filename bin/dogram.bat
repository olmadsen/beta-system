@echo off

if "%1"=="" goto missing
if "%2"=="" goto start
goto missing

:start
echo generator
call gen %1

echo bobsit version 1.6
call NTIexbobs < %1-parser.bobs
if not exist bobslist goto KEEPGOING
if exist %1-parser.lst del %1-parser.lst
rename bobslist %1-parser.lst
:KEEPGOING

echo "End-of-BOBS"
if not exist tables goto gramerrors

echo Creating tables (tabc version 1.6)
call tabc tables %1-parser

echo makepretty
call makepretty %1

echo morepretty
call morepretty %1

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




