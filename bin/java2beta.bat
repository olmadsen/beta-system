@echo off

rem Collect arguments.
set _opts_=
:getopts
if "%1"=="" goto java
set _opts_=%_opts_% %1
shift
goto getopts

rem Call the java program
:java
set CLASSPATH="%BETALIB%/javalib/java2beta/classes;%CLASSPATH%"
java -classpath %CLASSPATH% beta.converter.JavaConverter %_opts_% %BETALIB%

