@echo off

if "%1"=="" goto missing
if "%2"=="" goto start
goto missing

:start
echo generator
gen %1

goto done

:missing
echo "Usage: generator <grammar-name>"
goto done

:gramerrors
echo ERRORS IN GRAMMAR
echo Look at %1-parser.lst
goto done

:done
rem Done




