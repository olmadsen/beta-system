
 Notes for the preliminary .NET version of the BETA language compiler.

  *****************************************************************
  *** PLEASE READ SECTIONS A, B, C, D BEFORE USING ANY OF THIS! ***
  *****************************************************************

DISCLAIMER
==========

This is a VERY PRELIMINARY release. The compiler and the generated
programs may fail fatally in many situations. 
USE AT YOUR OWN RISK!


A. Prerequisites
================

1. The Microsoft .NET Framework Final version must be installed.
   Download: 
   [http://msdn.microsoft.com/downloads/default.asp?url=/downloads/sample.asp?url=/msdn-files/027/000/976/msdncompositedoc.xml]
   Direct:
   [http://download.microsoft.com/download/.netframesdk/SDK/1.0/W98NT42KMeXP/EN-US/setup.exe]


B. Installation of BETA_Net
===========================

1. There is no installer.
   Simply unzip BETA_Net-<date>.zip. This will create a directory named
   BETA_Net.
   The compiler nbeta.exe resides in the bin subdirectory.
   Make sure you have the BETA_Net/bin directory in your search path, if
   you want to invoke the compiler from other directories.

2. Set BETALIB.
   You must set the environment variable BETALIB to the location of
   your BETA_net directory before using the compiler.
   Do this in 
     Start->Settings->Control Panels->System->Advanced->Environment Variables.

3. Example programs reside in the examples subdirectory.

4. Very preliminary background documentation (working notes) reside in the
   documentation subdirectory.
   

C. Using the compiler
=====================

1. The compiler is named 'nbeta.exe'.

2. The compiler is invoked from the commandline in a shell, e.g. from
   cmd.exe.
   Also known to work with cygwin bash [http://www.cygwin.com/setup.exe]

3. The compiler is invoked by typing
     > nbeta foo
   where foo.bet is a BETA source file containing the definition of
   the PROGRAM fragment.

4. The DLLs and EXEs produced by the BETA compiler should in general
   be verifiable (using peverify.exe).
   As a convenience the compiler can automatically verify each DLL/EXE
   just after it is produced. To do this invoke the compiler with
   switch 37, i.e.:
     > nbeta -s 37 foo.bet


D. Known preliminary issues
===========================

1. Currently only a subset of BETA is implemented.

2. All source files constituting an executable must currently reside
   in the same directory.
   We intent to generate strong assemblies and config files and/or use
   the Global Assembly Cache for solving this later.

3. Because of (1) and (2) the standard BETA libraries are NOT part
   of this preliminary distribution. Instead a minimal environment is
   present in examples/tstenv.bet.

4. At most one compiled program can reside in a given directory without
   recompilation. That is: If a program foo.bet is compiled into
   foo.exe in a directory and subsequently another program bar.bet 
   is compiled into bar.exe in that same directory then foo.exe will
   no longer function correctly.
   To recompile foo into a functional state do this:
     > del program.dll foo.astL
     > nbeta foo
   Alternatively you can force regeneration of alle files involved in
   foo by
     > nbeta -s 12 foo

5. BETA patterns used only as classes can be prefixed with the
   keyword "class" and BETA patterns used only as methods can likewise be
   prefixed with keyword "proc". This will reduce the number of
   generated .NET classes.


E. Using the CLR debugger(s)
===========================

1. For a description of debugging using DbgCLR, see
   doc/Debugging.html#dbgclr

2. For a description of debugging using CorDbg, see
   doc/Debugging.html#cordbg

3. Possibly we will later generate a foo.dln file for DbgCLR.exe


F. Using Visual Studio .NET
===========================

1. For a description of debugging using Visual Studio .NET, see
   doc/Debugging.html#vsnet

2. Possibly we will later generate a foo.sln file for Visual Studio.NET

3. We intend to investigate the many possibilities that Visual Studio
   offers, by letting it "know" the BETA language, e.g. having syntax
   coloring, allowing it to call the compiler as part of a build etc.


G. Cross language support
=========================

1. You may use libraries written in BETA in other languages.
   You just compile the BETA library, using 'nbeta -x' (no main
   entrypoint generation and no linking), and then reference it from
   the other language.
   An example is in Bclass.bet and BclassUser.cs. Compilation
   statements are:

     nbeta -x Bclass.bet
     csc /r:System.dll /r:dotnet/tstenv.dll /r:dotnet/Bclass.dll BclassUser.cs

   NOTICE: The DLLs generated for BETA files currently reside in the
   'dotnet' dub directory (to avoid cluttering the source directory).
   As described in the compilation directive you must therefore tell
   csc to find the DLL's in the 'dotnet' subdirectory.
   Also at run-time you must tell the .NET Framework where to find
   these DLLs. This is most easily done by making a config file like
   BclassUser.exe.config. The content is currently always the same as
   this file (i.e. independent of the actual executable).

   The .NET classes generated from the BETA patterns are not yet
   fully documented. Preliminary documentation (working notes) reside 
   in the documentation subdirectory.

2. BETA code can call code and use types from other languages.
   There are problems with handling assembly references for this,
   though.
   It is safe to use any class or method from assembly [mscorlib] and 
   [System.Windows.Forms] - the compiler simply generates external
   assembly declarations for these in all generated IL files.
   Currently, before using a class/method in an external non-BETA 
   assembly, it must be declared using the predefined patterns
   External and ExternalClass. See dotnettstenvbody.bet and hellobox.bet
   for examples.

3. The cross language support is expected to be significantly improved
   in a later version. E.g. we expect to make the compiler lookup the
   declarations in external non-BETA assemblies, thus avoiding the
   need for declaring these manually.


H. Further information
======================

If you have any questions, problems, comments etc. regarding BETA.Net,
please contact [mailto:beta@daimi.au.dk].

We intend to set up a web page with project description, academic
articles etc. at a later time.
