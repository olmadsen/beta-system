@echo off

rem used to boot beta compiler.
rem this one is tricky, since we cannot just set BETALIB
rem to the old value and invoke bin/beta in the old location: 
rem BETALIB *must* point to the stuff we are about to compile. 
rem So we introduce a variable OLD_BETALIB to point to the old 
rem location and duplicate the beta script.

rem --- configuration---
set OLD_BETALIB="e:\\beta"
set OLD_COMPILER_VERSION="52"
set OLD_BETARUN="e:\\beta\\betarun\\v2.9"

rem --- don't change below ---

if "%BETALIB%"=="" goto install

rem Try to guess which SDK is being used
if not exist "%OLD_BETALIB%"\bin\ms\ntibeta%OLD_COMPILER_VERSION%.exe set sdk=bor
if not exist "%OLD_BETALIB%"\bin\bor\ntibeta%OLD_COMPILER_VERSION%.exe set sdk=ms

rem Set SDK to either "bor" or "ms" for either Borland or Microsoft SDK.
if "%sdk%"=="" goto usage

rem Collect arguments and expand those expandable
set _opts_=
:getopts
if "%1"=="" goto compile
if exist %1 goto name
set _opts_=%_opts_% %1
goto next
:name
for %%f in (%1) do set _opts_=%_opts_% %%f
:next
shift
goto getopts

:compile
rem Start the compiler
"%OLD_BETALIB%"\bin\%sdk%\ntibeta%OLD_COMPILER_VERSION% --betarun %OLD_BETARUN%\\nti\\%SDK\\betarunv.lib %BETAOPTS% %_opts_%

rem Clean-up
set _opts_=
set OLD_BETALIB=
set OLD_COMPILER_VERSION=
set OLD_BETARUN=
goto done

:usage
echo Please set the environment variable SDK to either ms or bor using:
echo   set SDK=ms
echo or
echo   set SDK=bor
goto done

:install
echo Please read the installation notes before trying to run the BETA compiler.
echo Thank you.
goto done

:done
rem Done
