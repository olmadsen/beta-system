@echo off

rem used to boot beta compiler.
rem this one is tricky, since we cannot just set BETALIB
rem to the old value and invoke bin/beta in the old location: 
rem BETALIB *must* point to the stuff we are about to compile. 
rem So we introduce a variable OLD_BETALIB to point to the old 
rem location and duplicate the beta script.

rem --- configuration---
set OLD_BETALIB="e:\\beta\\r4.1.boot"
set OLD_BETARUN="e:\\beta\\r4.1.boot\\betarun\\v3.0\\nti\\%SDK%\\betarun.lib

rem --- don't change below ---

if "%BETALIB%"=="" goto install

rem Set SDK to either "bor" or "ms" for either Borland or Microsoft SDK.
if "%sdk%"=="" goto usage

:SDK_OK
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
"%OLD_BETALIB%"\compiler\nti\%SDK%\beta.exe --betarun %OLD_BETARUN% %BETAOPTS% %_opts_%

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
