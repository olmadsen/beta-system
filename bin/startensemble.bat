@echo off

if "%BETALIB%"=="" goto set_betalib

if "%sdk%"=="gnu" goto sdk_set 
if "%sdk%"=="ms" goto sdk_set 
if "%sdk%"=="bor" goto sdk_set 
echo Environment variable SDK is not set.
goto install_notes

:sdk_set
rem Start the executable
if not exist "%BETALIB%"\distribution\v1.6\nti\%sdk%\ensembleDeamon.exe goto notexist
"%BETALIB%"\distribution\v1.6\nti\%sdk%\ensembleDeamon.exe
goto done

:set_betalib
echo Environment variable BETALIB is not set.

:install_notes
echo Please read the installation notes before trying to run the BETA compiler.
echo Thank you.
goto done

:notexist
echo EnsembleDeamon is not available for SDK=%SDK% 
goto done

:done
rem Done
