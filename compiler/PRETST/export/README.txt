Preliminary Windows release of BETA for pre-vm.

PRE Setup
---------
It is assumed that you have a working PalCom Runtime Environment set up,
specificly that you can call "pre-asm", "pre-st", and "pre-vm" from the command line.

Windows setup
-------------
If you use Windows Command Prompt (cmd.exe), you can augment your setup 
for PRE-BETA by issuing the command

  .\\configuration\\cmd_setup.bat

If you are using the cygwin bash shell, you can instead use

  . configuration/cygwin_bash_setup.sh

Notice the initial dot (.) at the beginning of the line.

This will set up needed environment variables and change directory to the 
"examples" directory.

Unix setup
----------

If you are using the T-shell (tcsh) you can augment your setup for
PRE-BETA by issuing the command

  source configuration/tcshrc

If you are using the bash shell, you can instead use

  . configuration/bash_setup.sh

Notice the initial dot (.) at the beginning of the line.


Examples
--------
The .bet files in the examples directory can be compiled and run using 
"pre-beta".

Compiling, e.g. beer.bet is done as such:
   pre-beta beer

LINUX NOTE: Due to a compiler bug, you may get the error
    Error while processing fragment group:
        .../examples/minienvbody
    The fragment group is reached twice during dependency analysis
    Circularity in fragment structure (origin and/or include)
  In this case, just restart pre-beta.

The compilation will result in a script file "beer" ("beer.bat" on windows), 
which calls pre-vm with the components generated from the BETA compilation.

The .st and .som files in the examples directory are SmallTalk
components currently needed for implementation purposes.

