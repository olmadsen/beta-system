@echo off

if "%BETALIB%"=="" goto install

rem Try to guess which SDK is being used
if not exist "%BETALIB%"\compiler\nti\ms\beta.exe set sdk=bor
if not exist "%BETALIB%"\compiler\nti\bor\beta.exe set sdk=ms

rem Set SDK to either "bor" or "ms" for either Borland or Microsoft SDK.
if "%sdk%"=="" goto usage

rem Start the executable
if not exist "%BETALIB%"\distribution\v1.6\nti\%sdk%\ensembleDeamon.exe goto notexist
"%BETALIB%"\distribution\v1.6\nti\%sdk%\ensembleDeamon.exe
goto done

:usage
echo Please set the environment variable SDK to either ms or bor using:
echo   set SDK=ms
echo or
echo   set SDK=bor
goto done

:install
echo Please read the installation notes before trying to Valhalla.
echo Thank you.
goto done

:notexist
echo EnsembleDeamon is not available for SDK=%SDK% 
goto done

:done
rem Done
