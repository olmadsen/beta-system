@echo off

if "%BETALIB%"=="" goto set_betalib

if "%sdk%"=="gnu" goto sdk_set 
if "%sdk%"=="ms" goto sdk_set 
if "%sdk%"=="bor" goto sdk_set 
echo Environment variable SDK is not set.
goto install_notes

:sdk_set
rem Collect arguments and expand those expandable
set _opts_=
:getopts
if "%1"=="" goto execute
if exist %1 goto name
set _opts_=%_opts_% %1
goto next
:name
for %%f in (%1) do set _opts_=%_opts_% %%f
:next
shift
goto getopts

:execute
rem Start the excutable

echo bobsit version 1.6
%BETALIB%\bobsgen\v1.6\nti\%SDK%\NTIexbobs < %_opts_%-parser.bobs

if not exist bobslist goto KEEPGOING
if exist %_opts_%-parser.lst del %_opts_%-parser.lst
rename bobslist  %_opts_%-parser.lst
:KEEPGOING

echo "End-of-BOBS"

if not exist tables goto gramerrors

echo Creating tables (tabc version 1.6)
%BETALIB%\bobsgen\v1.6\nti\%SDK%\tabc tables %_opts_%-parser

rem Clean-up
set _opts_=
goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run bobsit.
echo Thank you.
goto done

:gramerrors
echo ERRORS IN GRAMMAR
echo Look at %_opts_%-parser.lst
goto done

:missing
echo "Usage: bobsit <grammar-name>"
goto done

:done
rem Done
