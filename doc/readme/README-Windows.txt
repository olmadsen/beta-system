Mjolner Informatics ApS
Science Park Aarhus
Gustav Wieds Vej 10
DK-8000 Aarhus C, Denmark


Phone: +45 86 20 20 00
Fax. +45 86 20 12 22
E-mail: support@mjolner.com
URL:  http://www.mjolner.com




The Mjolner System release 4.1


                             
Installation guide for Windows 95/ Windows NT    November 1997
==============================================================


READ THE LICENCE AGREEMENT CAREFULLY BEFORE USING THE SOFTWARE


Requirements:
-------------

Requirements for using The Mjolner System on Windows NT/95 (Intel CPU):

  * CPU: 386/486/586/Pentium.
  * RAM: At least 16Mb RAM. 32Mb (or more) recommended.
  * Free disk space: Approximately 70Mb
  * Linker and standard C libraries from either Microsoft (recommended), 
    GNU (mingw32 with GCC earlier than 2.8), or Borland. 
    To use with Borland you also need the Assembler (details below).
  * Windows 95 or Windows NT 3.5.1 or later.


Contents:
---------

The distribution contains:
- BETA Compiler version 5.3
  including the compiler and basic libraries
- Lidskjalv - the platform independent GUI framework
- BETA and library demo programs
- Sif - The Mjolner BETA Browser and Editor
- Frigg - The Mjolner BETA Interface Builder
- Valhalla - The Mjolner BETA Debugger

Installation:
-------------

1. To install The Mjolner System, run the Setup Program found 
   or the CD in the folder named 

          Disk1

   (If you got the files through the internet, you should "unzip" 
   the file beta_<SDK>.zip first)

   The Setup Program installs The Mjolner System on your system 
   in the directory you specify.
   
   NOTES: If you are installing on Windows NT you must have Administrator
          privileges. Otherwise no program group will be created.

          You must NOT install the Mjolner System in a directory that 
          contains spaces in the path. 


2. When the installation is completed you should make sure that the 
   batch file to start the BETA compiler is in your path. If you
   installed The Mjolner System in e.g. C:\BETA, the batch file
   is located in C:\BETA\bin\beta.bat. You will also need to set the
   environment variables BETALIB, SDK and ASM_VERSION. In addition 
   the environment variables for your SDK must be set.

   BETALIB 
     should point to the location of the installation directory of the 
     Mjolner System, e.g. C:\BETA.

   SDK
     should be the name of the software development kit being used 
     (either ms, gnu or bor). 

   ASM_VERSION
     specify what assembler version to use with the SDK. Use:

     ASM_VERSION=6   for Microsoft (Even though no assembler is used)
     ASM_VERSION=1   for Gnu (Even though no assembler is used)
     ASM_VERSION=4   for Borland TASM32.EXE

     For SDK=bor ASM_VERSION=4 is default.

   The setup for Microsoft could look something like:

     PATH=C:\BETA\BIN;C:\MSDEV\BIN;%PATH%
     set LIB=C:\MSDEV\LIB;
     set BETALIB=C:\BETA
     set ASM_VERSION=6
     set SDK=ms

   The setup for Gnu could look something like:

     PATH=C:\BETA\BIN;C:\MINGW32\USR\BIN;C:\CYGNUS32\USER;%PATH%
     set LIB=C:\MINGW32\USR\LIB;
     set BETALIB=C:\BETA
     set ASM_VERSION=1
     set SDK=gnu

   The setup for Borland could look something like:

     PATH=C:\BETA\BIN;C:\BC45\BIN;%PATH%             
     set LD_LIBRARY_PATH=C:\BC45\LIB;
     set BETALIB=C:\BETA
     set ASM_VERSION=4
     set SDK=bor

   You can make Windows NT set the environment variables automatically 
   each time you log in via the System tool in the Control Panel.

   You can make Windows 95 set the environment variables automatically 
   each time you log in by setting them in the file c:\autoexec.bat.
  
   If you install the Mjolner System for more than one SDK, you can 
   use the same location for all installations, as most of the files 
   are shared.

3. To use The Mjolner System you must also install the either:

   a) the Microsoft Win32SDK including:
      - a linker: LINK.EXE
      - a make program: NMAKE.EXE (optional)
      - C libraries
      These can be obtained through e.g. Microsoft Visual C++ v4.0.

   b) the Gnu Win32SDK including:
      - a linker: LD.EXE and GCC.EXE
      - a make program: GMAKE.EXE (optional)
      - C libraries

   c) the Borland C++ and the Borland assembler.


   Installing the Microsoft Win32SDK.
     You will need to install the Microsoft SDK including all
     library files. Also, make sure that you have the LINK.EXE
     program in your path. This program may not be installed
     automatically -- if this is the case simply locate it on 
     your CD-ROM and copy it to a directory in your path. 


   Installing the Gnu Win32SDK.
     Getting the files:
     Go to Mjolner Informatics at:
	<http://www.mjolner.dk/download/gnu-software.html>
     Then follow the instructions for the installation.

   Installing the Borland C++ and Borland assembler.
     You will need to install Borland C++ for Windows NT/95 version
     4.5 or later. You will need to set an additional environment
     variable LD_LIBRARY_PATH to point to the directory containing
     the Borland library files. It will probably be probably be
     something like C:\BC45\LIB. Also install the Borland assmbler
     (please see the notes below).

     If you use the Borland Assembler with Windows 95 you will need a
     patch for TASM32. The patch is available from the Borland 
     "Patchs Available" WWW Page at 

       http://loki.borland.com/cpp/Patchs.htm. 

     The patch is directly available by FTP from

       ftp://ftp.borland.com/pub/techinfo/techdocs/language/tools/
       turboasm/ta4p01.zip. 

     If you install Borland Assembler you must make sure that you
     remove the linker if it is version 1.0 as it does not work with
     Windows 95. The linker supplied with Borland C++ works fine.


4. Online manuals

    The manuals are available in PDF format. We suggest to use the WWW
    page: %BETALIB%/doc/index.html as a convenient interface to the
    manuals.


5. The Emacs Editor

    If you want to use the very popular GNU Emacs text editor as an
    alternative to the Sif hyper structure editor included in the Mjolner
    System, you may benefit from the beta-mode for Emacs located in
    the file %BETALIB%/emacs/v1.7/beta-mode.el.

    By putting the following lines of Emacs-Lisp code into your .emacs
    file, you can make Emacs automagically recognize your BETA source code
    file if they have the suffix .bet (textual BETA files).
    
    (setq betalib (getenv "BETALIB"))
    (if (not betalib) (setq betalib "/usr/local/lib/beta"))
    
    (setq load-path (append load-path 
    			      (list (format "%s/emacs/current" betalib))))
    
    (autoload 'beta-mode "beta-mode")
    (setq auto-mode-alist (append (list (cons "\\.bet$" 'beta-mode))
    				    auto-mode-alist))
    
    When in beta-mode, you can get to know more about beta-mode by using
    M-x describe-mode.
   
    Also you may want to byte-compile beta-mode.el from within Emacs for
    improved performance. The directory %BETALIB%/emacs/v1.7/ also contains
    various other contributions for using Emacs to edit BETA programs.
    For instance, the file beta-hilit19.el contains a setup for syntactic
    colouring of your BETA programs when using Emacs version 19.


6. Introductory material

   You may find introductory material in the distribution in
   doc/Manuals/r4.1/#tutorials.

7. Tools to use

   a. Compiler

      The compiler to use is named "beta".

      You can run the BETA compiler either by:
      1) simply typing "beta <enter>" at the prompt in your favorit shell,
         e.g. "4DOS for Windows NT".
      2) double clicking the compiler icon in the program group that was 
         created during the installation.

      For a list of legal options use

         beta --help

      Compiling and executing a BETA program:

      1) Copy a demo program from demo directory to your working
         directory:

            copy %BETALIB%\demo\beta\record.bet .
            copy %BETALIB%\demo\beta\recordlib.bet .

      2) Compile the record program (record.bet):

         beta record

      3) Execute the record program:

         record

      Manual: "BETA Compiler", Reference Manual, MIA-90-2

   b. Sif

      Execute as follows:

      sif [file]

      Manual: "Sif: Mjolner Source Browser and Editor",
              Tutorial and Reference Manual. MIA 90-11

   c. Frigg

      frigg [projectname]

      Manual: "Frigg: Mjolner BETA Interface Builder",
              Tutorial and Reference Manual. MIA 90-33

   d. Valhalla

      tcsh> valhalla [executable]

      Manual: "Valhalla: The BETA Source-level Debugger",
              Tutorial and Reference Manual, MIA 92-12


9. Error reports

   The following email address can be used to send error reports and
   comments:

   support@mjolner.com

   The following classification of errors can be used to indicate
   which priority an error should have in the maintenance process.

   B:   Serious bug:
        The tool crashes or produces a wrong result and
        the error cannot be circumvented.
   b:   Minor bug,
        The tool produces a wrong result but
        the error can be circumvented
   I:   Serious inconvenience
        E.g. lack of important functionality.
   i:   Minor inconvenience
        Ex. lack of functionality that "would be nice to have",
        but is not crucial.

   An error report should include
   . a small description the steps that lead to the the error situation
     (if possible)
   . output from the console (if available)
   . dumps (if available)


Notes:
------

The file "DelsLog.1" located in %BETALIB% is a file used by the
uninstall mechanism. It should not be deleted.
 

Limitations:
------------

Known limitations in this release:

* Some parts of systemenv are still not implemented.
  Some of the demos in demo\basiclib\systemenv fails.
  Specificaly using the operation "keyboard.get" will block 
  the program, not only the current "system" (in systemenv-sense).

* Binary/ASCII files has a work-around (kludge) to compensate for a
  bug(?) in Windows NT/95. If a text file with UNIX style EOL characters
  (\n) is opened as a text file the offset (ftell) of the first
  character in the file is the negative of the number of '\n's found
  in the first 512 bytes. The kludge is that if a file is opened as a
  text file and a '\n' (UNIX EOL) is found before '\r\n' (Windows NT
  EOL) it will be opened as a binary file.

* File time stamps have proven difficulties in BETA on Windows NT. We
  (at GMT+1) experience the problem that files are reported to have a
  timestamp one hour less than the real time stamp of the file. This
  also means that when touching a file entry the file will be touched
  with a wrong time stamp (in out case one hour later than the real
  time).


