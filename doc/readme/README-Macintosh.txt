Mjolner Informatics ApS
Science Park Aarhus
Gustav Wieds Vej 10
DK-8000 Aarhus C, Denmark


Phone: +45 86 20 20 00
Fax. +45 86 20 12 22
E-mail: support@mjolner.com
URL:  http://www.mjolner.com




The Mjolner System release 4.1
                             

                             
Installation guide for Power Macintosh           November 1997
==============================================================
                             

READ THE LICENSE AGREEMENT CAREFULLY BEFORE USING THE SOFTWARE

This manual describes how to use the Mjølner System release 4.1 on
Macintosh.

The current version of the BETA compiler on the Macintosh is
available as a MPW tool. MPW stands for "Macintosh Programmers
Workshop", which is the official programming environment for the
Macintosh, developed by Apple, Inc.. The BETA compiler runs as a MPW
tool, that is, it is a command, that can be invoked from the MPW
Shell (command interpreter).  MPW 3.4 or later is needed to use
BETA.  In addition to the MPW Shell, the compiler uses the MPW Link
and Rez tools to build the programs.

Free Download of MPW
====================
As of october 1997, Apple has decided to make MPW freely available
for downloading.  It can be downloaded from

	ftp://dev.apple.com/devworld/Tool_Chest/Core_Mac_OS_Tools/

The current versions of the packages needed are

	MPW-3.4.2.sit.hqx
	Interfaces_Libraries-3.0.1.sit.hqx

Please notice, that new versions may be available when you read this.

CodeWarrior MPW
====================
As an alternative to Apple's MPW, a MPW package is included in the
MetroWerks CodeWarrior package.  Information about MetroWerks can be
found at

	http://www.metrowerks.com/

Information about MetroWerks CodeWarrior can be found at

	http://www.metrowerks.com/products/cw/


Additional Configuration for CodeWarrior MPW
============================================

Using the CodeWarrior version requires additional configuration. The
name of the CodeWarrior link tool is MWLinkPPC, whereas the name of
the linker in the MPW from Apple is PPCLink. The BETA compiler must
be instructed to use the MWLinkPPC tool instead. This is done by
inserting the following line in a MPW UserStartup file:

	set -e betaopts -s 70

A MPW UserStartup is a file with a name like UserStartup•john
that are located in the MPW folder.  An alternative method is to
rename the MWLinkPPC tool to PPCLink.

System Requirements:

Furthermore, the compiler requires a minimum machine configuration
of 40 MB of memory and a Power Mac processor (or Performa with RISC
processor), and a harddisk with at least 60 - 100 mb of free space
(depending on the size of the harddisk).


2	Installation Guide
==========================

This section describes how to unpack and install the Mjølner System
for Macintosh.  The section also includes description of memory
requirements to MPW and to BETA applications.

2.1	Contents
================

The distribution contains:
	* BETA Compiler v5.3
	* SifLight - The Mjølner Browser and Editor.
	* Basic libraries with text, stream, file, persistence, 
	  concurrency, etc.
	* Container libraries with collections, sets, lists, 
	  hashtables, sorting, etc.
	* Lidskjalv, the platform independent object oriented graphical
	  user interface library, 
	* BETA demo programs, including demo programs of how to use 
	  BETA and how to use GuiEnv.

2.2	Installation
====================

2.2.1	Unpack the Distribution Floppies

This distribution is stored as a self-extracting archive. To install
the Mjølner System, doubleclick the self-extracting archive.

2.2.2	Configuring the Files

After the beta folder is installed you need to move the file
UserStartup•beta in the beta folder to the MPW folder (the folder
containing the MPW Shell).  The purpose of UserStartup+beta is to
set up the environment used by The Mjølner System. When starting MPW
the first time after you moved UserStartup+beta to the MPW folder,
you will be asked to select the beta folder. The position of the
beta folder will be remembered afterwards using the file
BetaStartup+Home in the MPW folder. If this file is deleted or you
move or rename the beta folder you will be prompted for the beta
folder again.  During the first startup UserStartup+beta also
creates the file BetaStartup+Menu.  In BetaStartup+Menu the ß menu
is defined as described below. You can modify this file to suit your
specific needs. In case it is deleted a new standard
Beta-Startup+Menu is created during the next startup of the MPW
Shell.  If the MPW package from MetroWerks CodeWarrior is used,
additional configuration is required: The name of the CodeWarrior
link tool is MWLinkPPC, whereas the name of the linker in the MPW
package from Apple is PPCLink. The BETA compiler will use the
PPCLink tool by default. The BETA compiler must be instructed to use
the MWLinkPPC tool instead. This is done by inserting the following
line in a MPW UserStartup file:

	set -e betaopts -s 70

A MPW UserStartup is a file with a name like UserStartup+john that
are located in the MPW folder.  An alternative method is to rename
the MWLinkPPC tool to PPCLink.


2.3	Memory Requirements 
===========================

2.3.1	Memory Requirements to MPW Shell

To ensure proper workings of MPW and the BETA compiler, you should
ensure, that enough memory is allocated for MPW. In order to run the
BETA compiler at least 15 MB of memory must be allocated to the MPW
Shell. The amount of memory can be set by selecting the MPW Shell
icon and using the Show Info command in the Finder as illustrated in
the figure below:
 
More memory allocated to MPW makes the compiler and especially the
linker run faster.

2.3.2	BETA Application Memory Requirements

	
You may have to increase the memory requirements of a compiled BETA
application (1,5 MB for a BETA application). This is done by
selecting the BETA application, and then use the Show Info command
in the Finder.


Using MPW Programmers Workshop
------------------------------

This section briefly describes how to use MPW for compiling and
running BETA applications.  MPW is a program development environment
for the Macintosh computers with tools for editing, compilation and
execution of e.g. BETA programs. MPW is a command driven interface
to the Macintosh operative system (analogous to the Unix shell).

MPW WorkSheet

MPW is centred around the concept of a worksheet, where the commands
are entered and thereafter executed. A worksheet saves its contents
from session to session and can therefore be used to contain the
most often used commands such that they can be easily executed in
later sessions. The commands in the worksheet can be edited using
the usual Macintosh editing facilities.

Commands can be executed from the worksheet in two different ways:
- The text cursor is placed somewhere in the command line and the Enter key
  is pressed. The entire line will then be executed as one command.
- Some text may be selected and the Enter key is pressed. 
  The selected text will then be executed as one command.

Using MPW for BETA programming

When starting MPW after installation, an environment is set up to
make it easy to use the BETA system. The BETA compiler can be
executed either using the script beta or by using the special BETA
menu.  Notice that you only need to activate the BETA compiler on
the program fragment that constitutes the application. If the
program fragment uses other fragments (libraries), these are
automatically included by the compiler and linker. If some fragments
have been changed since the last compilation, these fragments will
automatically be recompiled.


The BETA Menu
-------------

The BETA environment defines a BETA menu containing items which makes
it easy to use the BETA compiler.

The items are:
Compile {Active}        Compile the front most window
Recompile               Compile the previously compiled file again
Compile File...         Prompts the user for a file, and compiles the 
                        selected file
Commando BETA           Displays a dialogue for setting arguments and 
                        executing the BETA compiler
Execute                 Execute the last compiled file
Open Fragment           Tries to open the selection. 
			The selection is treated
                 	as a BETA file name, e.g. ~beta/guienv/v1.6/guienv
Directory {Active}      Changes directory to the front most window
  -Application          Compile the BETA program as an application (default)
  -Tool                 Compile the BETA program as a MPW Tool beta script

In most cases, the BETA menu defines the necessary interface to the
BETA compiler.  However, the advanced user may prefer to use the
beta script instead, please see [MIA 90-02].  When selecting Compile
{Active} the beta script is invoked with the active window as
argument. The script first executes the BETA compiler and then
executes the job file generated by the compiler. The job file links
the compiled application. Output during compilation is directed to a
separate MPW window.

Application and Tool

The options -Application and -Tool specify whether the generated
application should be a Macintosh stand-alone application or a MPW
tool. The default is that the application is linked as a Macintosh
stand-alone application. If a BETA program uses the input/output
streams keyboard and screen in betaenv and is executed as a
stand-alone Macintosh application, a simple console window is
opened. The input/output stream is redirected to this window. The
console also defines the standard File, and Edit menus. The Cut,
Copy, and Paste items in the Edit menus are available.  The execution
can be stopped by selecting Quit in the File menu.  Notice, that if
the program is using GuiEnv (e.g. Macintosh facilities like windows,
menus, etc.), it must be compiled as a stand-alone application. The
input/output is in this case redirected to a special GuiEnv window.


Introductory material
---------------------
   
You may find introductory material in the distribution in
doc/Manuals/r4.1/#tutorials.


Getting started
---------------

The following steps are usually performed when handling BETA
programs under MPW:

1. MPW is started by double clicking the MPW Shell icon or on a BETA
   source file (.bet). This opens MPW with the worksheet document in
   a window.

2. We now edit the BETA program text. 
   This may be initiated in two different ways:
   a) We open an existing BETA file by selecting the Open entry in 
      the File menu.
   b) We create a new file for the BETA program by selecting the New
      entry in the File menu. The file name must end with .bet.

3. Now edit the file using the ordinary Macintosh editing facilities 
   in the window containing the program.

4. Save the changed BETA program using the Save entry in the File menu.

5. Select Compile {Active} in the BETA menu.

6. Messages will now be written in the {MPW}:compilerOutput window. 
   These messages informs about the progress of the compilation, 
   and eventually about syntactic and semantic errors.

7. The program may now be executed by selecting Execute in the BETA menu.

8. Close MPW using the Quit entry in the File menu.
   Steps 3, 4, 5 and 7 may be repeated over and over, while making 
   changes to the same program.


Known bugs, limitations and inconveniences in release 4.1 for Power
Macintosh
==========================================================================

The current release 4.1 contains a number of known bugs,
limitations and inconveniences:

1. 	Link time is very long for BETA programs.
   	We have not been successful in getting appropriate 
   	documentation from Apple to make optimal generation
   	of the XCOFF files.

2. 	Freja is not yet available for PowerMac

3. 	Valhalla is not yet available for PowerMac

4. 	bobsit will not work, because the exbobs program 
   	did not get ready for r4.1.

5. 	Problems with Sif
   	- Closing a workspace may make the machine crash

6. 	Check for suspend involving callbacks is not done. 
   	If you do a suspend in a callback situation the program 
   	is likely to crash.

7. 	Integer division by zero will yield unpredictable results 
   	(should be caught as an exception as on other platforms).

8. 	The pattern doGC in betaenv does not work on ppcmac. 
   	This is used in implementation of 
   	   sysutils/v1.5/scanobjects
   	used in the demo 
   	   demo/sysutils/objinterface/scanobj
   	which consequently does not work

9.	The PutReal pattern in ~beta/basiclib/v1.5/numberio does not work.
	This is used in the demo programs in
		~beta/demo/basiclib/reals/
	and
		~beta/demo/basiclib/random/tstgenchi.bet
	which does not produce a correct output.

11.	The touch and modtime.set operations on diskentry does not work

12.	The iget operation on keyboard is not implemented.
	This is used in the demo programs in:
		~beta/demo/basiclib/iget/
	which consequently does not work

13.	Systemenv is not implemented

14.	Process is not fully implemented.
	Some of the socket stuff works, though.

15.	Bifrost is not implemented

16.	Frigg is not available.

18.	There is a number of problems with GuiEnv:
	- There is no support for resources like icons, cursors etc.
	- There are some update problems.
	- The only way to make a window appear like a modal dialog is by
	  furtherbinding "menubarVisible" to exit false.
	- figureItems does not work yet.  

19.	The "Command BETA" command in the Beta menu, does not work
