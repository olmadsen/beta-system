@echo off

if "%BETALIB%"=="" goto set_betalib

if "%objdir%"=="nti_ms" goto objdir_set
if "%objdir%"=="nti_gnu" goto objdir_set
if "%objdir%"=="nti_bor" goto objdir_set

if "%sdk%"=="gnu" goto sdk_set 
if "%sdk%"=="ms" goto sdk_set 
if "%sdk%"=="bor" goto sdk_set 
echo Environment variable SDK is not set.
goto install_notes

:sdk_set
rem Collect arguments.
set _opts_=
:getopts
if "%1"=="" goto compile
set _opts_=%_opts_% %1
shift
goto getopts

:objdir_set
rem Collect arguments.
set _opts_=
:getopts2
if "%1"=="" goto compile2
set _opts_=%_opts_% %1
shift
goto getopts2

:compile2
rem Start the compiler
%BETALIB%\bin\%objdir%\beta.exe %BETAOPTS% %_opts_%
rem Clean-up
set _opts_=
goto done

:compile
rem Start the compiler
%BETALIB%\compiler\nti\%sdk%\beta.exe %BETAOPTS% %_opts_%
rem Clean-up
set _opts_=
goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run the BETA compiler.
echo Thank you.
goto done

:done
rem Done
