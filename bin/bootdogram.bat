@echo off

rem Used to boot grammars by invoking the 
rem grammar tools of the previous release.

rem --- configuration---
set OLD_BETALIB=e:\beta\r4.1.boot
set META_VERSION=v5.2
set BOBSGEN_VERSION=v1.6
set PRETTYGEN_VERSION=v5.2

rem --- don't change below ---

if "%BETALIB%"=="" goto set_betalib

if "%sdk%"=="gnu" goto sdk_set 
if "%sdk%"=="ms" goto sdk_set 
if "%sdk%"=="bor" goto sdk_set 
echo Environment variable SDK is not set.
goto install_notes

:sdk_set 
if "%1"=="" goto missing

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
rem Start the grammar tools
set _myopts_=%_opts_%

rem call %OLD_BETALIB%\bin\generator %_myopts_%
echo generator version %META_VERSION% 
"%OLD_BETALIB%\meta\%META_VERSION%\NTIgen" %_opts_%

rem call %OLD_BETALIB%\bin\bobsit %_myopts_%
echo bobsit version %BOBSGEN_VERSION%
%OLD_BETALIB%\bobsgen\%BOBSGEN_VERSION%\NTIexbobs < %_opts_%-parser.bobs
if not exist bobslist goto KEEPGOING
if exist %_opts_%-parser.lst del %_opts_%-parser.lst
rename bobslist  %_opts_%-parser.lst
:KEEPGOING
echo "End-of-BOBS"
if not exist tables goto gramerrors
echo Creating tables (tabc version 1.5)
%OLD_BETALIB%\bobsgen\%BOBSGEN_VERSION%\NTItabc tables %_opts_%-parser
:gramerrors
echo ERRORS IN GRAMMAR
echo Look at %_opts_%-parser.lst

rem call %OLD_BETALIB%\bin\makepretty %_myopts_%
echo makepretty version %PRETTYGEN_VERSION% 
"%OLD_BETALIB%\prettygen\%PRETTYGEN_VERSION%\NTImakepretty" %_opts_%

rem call %OLD_BETALIB%\bin\morepretty %_myopts_%
echo morepretty version %PRETTYGEN_VERSION% 
"%OLD_BETALIB%\prettygen\%PRETTYGEN_VERSION%\NTImorepretty" %_opts_%



rem Clean-up
set _opts_=
set OLD_BETALIB=
set META_VERSION=
set BOBSGEN_VERSION=
set PRETTYGEN_VERSION=

goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run the BETA compiler.
echo Thank you.
goto done

:missing
echo "Usage: dogram <grammar-name>"
goto done

:done
rem Done
