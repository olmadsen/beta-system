@echo off

if "%BETALIB%"=="" goto install

rem Try to guess which SDK is being used
if not exist "%BETALIB%"\system\v5.2\nti\ms\beta.exe set sdk=bor
if not exist "%BETALIB%"\system\v5.2\nti\bor\beta.exe set sdk=ms

rem Set SDK to either "bor" or "ms" for either Borland or Microsoft SDK.
if "%sdk%"=="" goto usage
if not "%1"=="" goto missing

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
"%BETALIB%"\objectbrowser\v2.1\psbrowser\psbrowser %_opts_%

rem Clean-up
set _opts_=
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
echo "Usage: psbrowser"
goto done

:done
rem Done




