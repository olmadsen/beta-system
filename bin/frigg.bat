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
rem Start the executable
"%BETALIB%\interfacebuilder\v1.6\nti\%sdk%\frigg" %_opts_%

rem Clean-up
set _opts_=
goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run frigg.
echo Thank you.
goto done

:done
rem Done
