Mjolner Informatics ApS
Science Park Aarhus
Gustav Wieds Vej 10
DK-8000 Aarhus C, Denmark


Phone: +45 86 20 20 00
Fax. +45 86 20 12 22
E-mail: support@mjolner.com
URL:  http://www.mjolner.com




The Mjolner System release 4.1
                             

                             
Installation guide for UNIX workstations         November 1997
==============================================================


READ THE LICENCE AGREEMENT CAREFULLY BEFORE USING THE SOFTWARE


Requirements:
-------------

Sun SPARC:                  Solaris 2.3, 2.4, 2,5, 16 MB, 32Mb recommended.
HP9000/700:                 HP-UX 9, 16 MB, 32Mb recommended.
Silicon Graphics:           IRIX 5.3 or later, 16 MB, 32Mb recommended.
Intel 386/486/586/Pentium:  Linux 1.2 (ELF) or later, 8Mb, 16-32Mb recommended.
                            (Read the BETA-FAQ about glibc problems)

X window system (Rel. 11.3 or newer), 
Motif 1.2 or later (not required for textual BETA programs),
150 MB disk space.
The installation is approx. 100 MB + documentation approx. 13 MB.


Contents:
---------

The distribution contains:
- BETA Compiler version 5.3
  including the compiler and basic libraries
- Lidskjalv - the platform independent GUI framework
- BETA and library demo programs
- Sif - The Mjolner BETA Browser and Editor
- Valhalla - The Mjolner BETA Debugger (currently not on hpux9pa)
- Freja - The Mjolner BETA CASE Tool (currently only Sun4 Solaris & Linux)
- Frigg - The Mjolner BETA Interface builder




Installation:
-------------

The file configuration.lst contains a list of the version numbers
of each component of the system.

1. Get the files:

   Copy the BETA system .Z files from the media, delivered by Mjolner 
   Informatics.  Either ftp (get) in binary mode (bin), or copy from
   diskettes/tapes/CD-ROM (depending on the delivery method).
   The details varies from system to system.

   Notice, on the Linux system is compressed using gzip, 
   thus the extension is .gz instead on .Z.

2. Unpack the files, if necessary:

   Each of the compressed files should now be unpacked; use either e.g.

        uncompress system.tar.Z 
        tar -xvf system.tar
      
    or (if zcat is available)
      
        zcat system.tar.Z | tar -xvf -
      
    On Linux systems use:
      
        tar -xzvf system.tar.gz
      
    Repeat this for the other .Z files too.

    You can also use the install4.1.unix script, but you might need to
    modify it.

3. Set-up the system:

   a. Include $BETALIB/bin in your search path:

      The environment variable BETALIB must be set, in order to specify
      the directory, where you have installed the system e.g.:

        setenv BETALIB /usr/smith/beta

      or when using bash on Linux:

        bash$ BETALIB=/usr/smith/beta
        bash$ export BETALIB

      The location of the BETA system in your file directory is in the
      following referred to as $BETALIB.

   b. Set-up the search path:

      The path must include $BETALIB/bin:

      tcsh> set path=( $BETALIB/bin $path )

      You may need to do a "rehash" if you set this manually in the shell
      (as opposed to setting it in your .login file).
  
   c. If you use the window manager (TV)TWM, you can enable automatic
      placement of dialogs etc. by including the following
      in your .twmrc file:

       UsePPosition "non-zero"

   d. Scripts in $BETALIB/bin

      The scripts located in $BETALIB/bin use an internal script to perform
      some tests for, e.g., machine type. This script is placed in 
           $BETALIB/configuration/env.sh. 
      If you have a very special installation, it may be necessary to modify
      the env.sh script according to your system.
      If the $BETALIB is not set, env.sh sets it to /usr/local/lib/beta.

   e. Make Current Links

      Many of the examples in the system manuals use the notation 
      ~beta/<library>/current/ to describe the version of libraries in the
      current release of the Mjolner System.  In each directory current
      is a link to the current version of the library. The current links can
      be generated using the make_currentlinks script supplied with the
      Mjolner System. 

4.  Online manuals

    Standard UNIX manual pages for the tools in the Mjolner System are 
    placed in $BETALIB/man/current/man1. To include these in the search path of
    the man program, either include $BETALIB/man/current/ in your MANPATH
    environment variable, or have your system administrator copy the files 
    in $BETALIB/man/current/man1 to the directory containing local manual pages
    (usually /usr/man/manl).

    The manuals are included in PDF format. We suggest to use the WWW page:
    $BETALIB/doc/Manuals/index.html as a convenient interface to the manuals.

5.  The Emacs Editor

    If you want to use the very popular GNU Emacs text editor as an
    alternative to the Sif hyper structure editor included in the Mjolner
    System, you may benefit from the beta-mode for Emacs located in 
    the file $BETALIB/emacs/current/beta-mode.el.  

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
    improved performance. The directory $BETALIB/emacs/current also contains
    various other contributions for using Emacs to edit BETA programs.
    For instance, the file beta-hilit19.el contains a setup for syntactic
    colouring of your BETA programs when using Emacs version 19.

6.  Motif on SunOS and Linux

   If you are running SunOS 4.x or Linux, then Motif is normally not
   included in the standard libraries on your machine. You will then have
   to buy a separate Motif package (version 1.2 or later) in order to use
   the graphical tools and libraries included in the Mjolner System.

   After you have installed such a package, you should change the two
   environment variables MOTIFINC and MOTIFHOME, which are set in the
   $BETALIB/configuration/env.sh file to reflect the placement of
   your Motif installation.

7. Introductory material

   You may find introductory material in the distribution in
   doc/Manuals/r4.1/#tutorials.

8. Getting started.

   a. Compiler

      The compiler to use is named "beta".

      For a list of legal options use "man beta" or

      tcsh> beta --help

      Compiling and executing a BETA program:

      1) Copy a demo program from demo directory to your working
         directory:

            cp ${BETALIB}/demo/beta/record.bet .
            cp ${BETALIB}/demo/beta/recordlib.bet .

      2) Compile the record program (record.bet):

      tcsh> beta record

      3)    Execute the record program:

      tcsh> ./record

      Manual: "BETA Compiler"
               Reference Manual, MIA-90-2

   b. Sif

      tcsh> sif [file]

      Manual: "Sif: Mjolner Source Browser and Editor", 
              Tutorial and Reference Manual. MIA 90-11

   c. Frigg

      tcsh> frigg [projectname]

      Manual: "Frigg: Mjolner Interface Builder", 
              Tutorial and Reference Manual. MIA 90-33

   d. Valhalla

      tcsh> valhalla [executable]

      Manual: "Valhalla: The Source-level Debugger",
              Tutorial and Reference Manual, MIA 92-12

   e. Freja

      tcsh> freja [file]

      Manual: "Freja an object-oriented CASE tool", 
              Tutorial and Reference Manual, MIA 93-31             

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


