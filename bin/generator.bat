@echo off

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
rem Start the eexcutable
echo generator version 5.2
"%BETALIB%\meta\v5.2\nti\%SDK%\gen" %_opts_%

rem Clean-up
set _opts_=
goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run the BETA compiler.
echo Thank you.
goto done

:missing
echo "Usage: generator <grammar-name>"
goto done

:done
rem Done




