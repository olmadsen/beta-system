@echo off

rem Used to boot grammars by invoking the 
rem grammar tools of the previous release.

rem --- configuration---
set OLD_BETALIB=e:\beta

rem --- don't change below ---

set NEW_BETALIB=%BETALIB%
set BETALIB=%OLD_BETALIB%

rem Try to guess which SDK is being used
if not exist "%BETALIB%"\bin\ms\ntibeta52.exe set sdk=bor
if not exist "%BETALIB%"\bin\bor\ntibeta52.exe set sdk=ms

rem Set SDK to either "bor" or "ms" for either Borland or Microsoft SDK.
if "%sdk%"=="" goto usage
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
call %BETALIB%\bin\generator %_myopts_%
call %BETALIB%\bin\bobsit %_myopts_%
call %BETALIB%\bin\makepretty %_myopts_%
call %BETALIB%\bin\morepretty %_myopts_%


rem Clean-up
set BETALIB=%NEW_BETALIB%
set _opts_=
set OLD_BETALIB=
set NEW_BETALIB=

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

:missing
echo "Usage: dogram <grammar-name>"
goto done

:done
rem Done




