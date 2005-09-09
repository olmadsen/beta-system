:: ROTOR CLIX Wrapper     
@echo off                 
set BETART=NoNYI:%BETART%
set _opts_=               
:getopts                  
if "%1"=="" goto execute 
set _opts_=%_opts_% %1 
shift                     
goto getopts              
:execute                  
clix %BETALIB%\bin\managed-nbeta.exe %_opts_% 
