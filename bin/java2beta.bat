@echo off

rem Collect arguments.
set _opts_=
:getopts
if "%1"=="" goto compile
set _opts_=%_opts_% %1
shift
goto getopts

rem Call the java program
%BETALIB%\bin\%objdir%\beta.exe %BETAOPTS% %_opts_%


java -classpath %%BETALIB%%\javalib\java2beta\classes beta.converter.JavaConverter %_opts_% %%BETALIB%%

