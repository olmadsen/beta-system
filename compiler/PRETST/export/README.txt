Preliminary Windows release of BETA for pre-vm.

Setup
-----
It is assumed that you have a working PalCom Runtime Environment set up,
specificly that you can call "pre-asm", "pre-st", and "pre-vm" from the command line.

If you use Windows Command Prompt (cmd.exe), you can augment your setup 
for PRE-BETA by issuing the command

.\\configuration\\cmd_setup.bat

If you are using the cygwin bash shell, you can instead use

. configuration/cygwin_bash_setup.sh

Notice the initial dot (.) at the beginning of the line.
This will set up needed environment variables and change directory to the 
"examples" directory.

Examples
--------
The .bet files in the examples directory can be compiled and run using "pre-beta".
Compiling, e.g. beer.bet is done as such:
   pre-beta beer
This will result in windows batch file "beer.bat", which calls pre-vm with the
components generated from the BETA compilation.

The .st files in the examples directory are SmallTalk components currently
needed for implementation purposes.

