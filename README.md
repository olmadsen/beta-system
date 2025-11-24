This reposotory contains **The Mjølner Beta System**, which consists of a compiler for Beta, a library of Beta patterns, and an SDE.

In addition, it contains **The qBeta System,** which consists of a compiler for qbeta, a library of qBeta objects and an SDE for qBeta.

**Beta** was developed by Bent Bruun Kristensen, Ole Lehrmann Madsen, Birger Møller-Pedersen and Kristen Nygaard. Here are some references:
1. B.B. Kristensen, O.L Madsen, B. Møller-Pedersen, K. Nygaard, Abstraction Mechanisms in the Beta Programming Language, POPL 1983.
2. O.L Madsen, B. Møller-Pedersen, K. Nygaard, Object-Oriented Programming in the Beta Programming Language, ACM, Addison Wesley, 1993. Out of print, but a PDF-file is available in this repository.
3. B. B. Kristensen, O.L Madsen, B. Møller-Pedersen, The When, Why and Why not of the Beta Programming Language, ACM SIGPLAN conference on History of Programming Languages (HOPL 2007) - San Diego, USA.

The MJølner Beta System was originally developed as part of the Nordic Mjølner Project and afterwards by Mjølner Informatics LtD. and Aarhs University.  The following people took part in the development, Peter Andersen, Lars Bak, Flemming Gram Kristensen,
Michael Christensen, Eric Corry, Mads Brøgger Enevoldsen, Kim Falk, Morten Grouleff, Jørgen Lindskov Knudsen, Stephan Erbs Korsholm, Michael Lassen, Ole Lehrmann Madsen, Claus Nørgard, Elmer Sandvad, Lennert Sloth,
+++ to be completed.

1. Object-oriented Environments: The Mjølner Approach, Jørgen Lindeskov Knudsen, Mads Løfgren, Boris Magnussen, Ole Lehrmann Madsen (eds.), Prentice Hall, 1994.

**qBeta** is a relatively new language developed by Ole Lehrmann Madsen and derived from Beta. Birger Møller-Pedersen has (and is) an importat contributor and Henry Michael Lassen is a key person in the development of the SDE.

# Installing The Mjølner Beta System
In this Section, we describe how to install The Mjølner Beta System (MBS) from GitHub.
MBS used to run on a number of platforms, including Linux, Mac, Windows, SUN, and others. 
MBS is currently only running on Windows 11 and Ubuntu-32.
Attempts have been made to make Beta run on Ubuntu-64 and MacOs, but so far this has not succeeded.

To gain access to the GitHub repository, mail to ```olm@cs.au.dk``` to be added as a collaborator.
We plan to make the repository public.

R5.5 is the newest version of MBS.

It is recommended to establish a directory called `beta` and then place `r5.5` in this directory.

```
...
mkdir beta
cd beta
```

To checkout the system do this:

```
git clone git@github.com:olmadsen/beta-system.git r5.5
```

This will create a local copy of the repository (called ```r5.5```) on your machine.

You can `git status`, `git diff`, `git add`, `git commit`, etc. relative to this local repository.

To propagate your changes to the official github repository use `git push.` To get contributions from others from the github repository to your own repository use `git pull`.

## About the postwimp library
The `postwimp` library is currently a separate repository on github.
To check it out separately use:

```
git clone git@github.com:olmadsen/beta-postwimp.git postwimp
```

You will most likely want to use it inside a beta-system clone (e.g. ```r5.5``` (as above). 
For this reason, `postwimp` has been added as a submodule to beta-system. So inside your ```r5.5``` clone, you can activate the submodule as such:

```
cd postwimp
git submodule init
git submodule update
```

You will then get the postwimp directory populated with the files, with changes separately tracked against the beta-postwimp.git repository.

If you are checking out the entire beta system, and would like to check out postwimp together with the rest, you can do it as such:

```
git clone --recurse-submodules git@github.com:olmadsen/beta-system.git r5.5
```

## MBS on Windows
Here we describe how to install MBS on a Windows machine. MBS is currently running on Windows 11.

It is recommended to to place the `beta` directory in `c:`:
```
cd c:
mkdir beta
cd beta
```
And then checkout `beta`from GitHub.

### Required Software

The Beta System uses some other software packages:

#### Microsoft Visual Studio .NET 2003

If you don't have access to VS2003, you may contact Ole Lehrmann Madsen at olm@cs.au.dk or Peter Andersen at Peter.andersen@alexandra.dk for help.

VS2003 can also be downloaded from the internet, only a selection of them are required.
E.g. from ```http://download.cnet.com/Microsoft-Visual-Studio-NET-2003-Service-Pack-1/3000-10250_4-10729888.html```.
30-08-2023 VS2003 is now included as a ZIP file in the setup directory in the root of the GIT checkout, see below.

**Correction: ** The above should probably be changed such that a user is recommended to place VS2003 in `C/Program Files`.

#### Using VS2003 linker

The Beta System uses the linker from VS2003.

So rename ```/usr/bin/link.exe``` to ensure that the linker from VS2003 is used.

The VS2003 linker named ```link.exe``` is located in the folder ```$VS2003/Vc7/bin```.

### Cygwin

Cygwin is a Unix-like shell  and accompanying command line tools for Windows.

An installer may be downloaded from:

```
http://cygwin.com/install.html
```

In addition to the default packages, you must include these packages:

* ```gcc-core```
* ```make```
* ```perl``` -  28-08-2023 : perl location now assumed to be ```/usr/bin/perl``` - if not, you may need to copy it to there. Check with ```which perl```.

You may want to add the following to ```C:/cygwin64/home/<username>/.inputrc```:

```
Ignore case while completing
set completion-ignore-case on
```

You may want to add the following to your `C:/cygwin64/home/<username>/.bashrc`:
```
Set cygwin window size to 100 chars wide, 60 lines high
echo -en "\e[8;60;100t";
```
### Setup of environment variables for cygwin ###
30-08-2023 The following complete setup works in newest cygwin 64 bit on Windows 11. Add to your C:/cygwin64/home/<username>/.bashrc

```
# Set up BETA environment
echo Setting up BETA r5.5
export BETALIB="c:/beta/r5.5"
export BETAOPTS="-s 38"
export MIASDK="ms"

# Set up PATH to include BETA binaries and administrative scripts (without using wrappers)
export CYGBETA=`cygpath $BETALIB` # for use in cygwin paths
export PATH="$CYGBETA/bin/nti_ms:$CYGBETA/bin/admin:${PATH}"

# Add Visual Studio 2003 to INCLUDE, PATH and LIB environment variables
export INCLUDE="c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Include/;c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include/;$INCLUDE"
export PATH="/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/SDK/v1.1/Bin:/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Bin/:/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/Common7/IDE/:$PATH"
export LIB="c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Lib/;c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Lib;$LIB"

# Set prompt to display BETA info, username, directory
PS1="\n[r5.5-$MIASDK]\n\[\033]0;\w\007\033[32m\]$USER@\h \[\033[33m\w\033[0m\]\n$ "
cd $BETALIB
```

### Compiling Beta programs

A Beta program in the file ```foo.bet``` may be compiled by executing

```beta foo```

# Installing The qBeta System

The text here is currently only an itemized draft and will be expanded.

* The qBeta System is currenlty in the folder ```MiniSystem``` - plans to rename to qBetaSystem
* QBS is part of MBS, so if you check-out MBS, you also have QBS.
* You must also install Cygwin as described above
* You don't need VS2003
* You must setup ```BETALIb``` as desribed above.
* You must add ```MiniSystem/bin/``` to your path.
* You find the qBeta library in ```MiniSystem/qBeta/BETAworld```
* The qBeta compiler may be invoked by ```qbeta foo``` where ```foo.qbeta``` is a qBeta program.
* The qBeta SDE may be invoked by ```qenv```.

# Further notes on The Mjølner Beta System
In this Section, we mention further issues regarding MBS.
Most of these issues are mainly notes for the developers of MBS and probably not relevant for most users of MBS.

### Running mbs_boot

To boot the Beta System run the command `mbs_boottrack`.

This, however, does unfortunately not work. Some time ago attempts were made to fix, but it was not completed.

Part of this has been to make MBS running on a 64-bit Linux.

Currently 3 Word files are attached - don't remember which one is the newest one - this has to be investigated. The file "OK - ..." is an email  correspondence with Henry Michael Lassen and seems older than the two other files, so we dont have to consider it.

BUT: booting the system should not be necessary since the necessary binaries are included in the checkout from GitHub.

30-08-2023 The following now works (with a few errors) on newest Cygwin 64bit, windows 11:

```
# Force re-parsing of everything
mbs_rmast -u
# Rebuild everything from scratch, with a copy of the output in boottrack.out
mbs_boottrack | tee boottrack.out
```

### Note on Beta programs using X-windows

Beta programs using the gui-library guienv requires that X-libraies are installed. 

#### Ubuntu
On Ubuntu there was an issue with the compiler on 

```beta bvmbeta```

gave this message from the linker

```
ld: cannot find -lXp
ld: cannot find -lXext
```

When trying to use
```
sudo apt install libx11-dev
sudo responds that this package is already installed
```
The following got It to work
```
sudo apt install libxext-dev
```

And from this page, we got ```libXp```:

```
https://www.ibm.com/support/pages/how-configure-ubuntu-1604-ubuntu-1804-or-ubuntu-2004-run-ibm-rational-clearcase
```
...

Additionally, X-based GUI ClearCase tools require the library `libXp`, which is not available on Ubuntu 16.04 or Ubuntu 18.04.

Note: As of ClearCase version 9.0.1.1 and version 9.0.0.5, the `libxp` package does not need to be installed.

That library is available on Ubuntu 14.04, you can install it using the following commands:

```
$ cd /tmp
$ wget http://mirrors.kernel.org/ubuntu/pool/main/libx/libxp/libxp6_1.0.2-1ubuntu1_i386.deb
$ sudo dpkg --install libxp6_1.0.2-1ubuntu1_i386.deb
```

In `/usr/lib/i386-linux-gnu`, we need to create a link in order for `libXp` to refer to the correct version.

```
sudo ln -s libXp.so.6 libXp.so
MBS on Ubuntu 64 
```

The proces described in the attached papers has led to a version of the Beta compiler that runs on 64-bit Ubuntu.

Recently the Eriks Ernst Betarun was just copied to ../beta/r5.5/lib/linux and then the compiler seems to work. At least it compiles compiler/TST/tst - but some (harmless?) warnings from compilation of C programs.
The compiler used is called beta64 in /home/olm - it is not clear how it was created;-)

But Beta seems to run on CS/AU 64-bit Ubuntu. HAs bee copied to /home/olm/beta/r5.5/bin/linux.

When compiling e.g. MiniSystem/qbeta/compiler.bet, gcc fails on Motif/X files – probably needs to be installed. See attempts below to install!?

#### 64-bits ubuntu stuff
64-bit Linux – at least Ubuntu 64 – cannot execute a 32-bit executable unless 32-bit libraries are installed. These may be installed as described here: installing 32-bit libraries .

To run a 32-bit executable file on a 64-bit multi-architecture Ubuntu system, you have to add the i386 architecture and install the three library packages `libc6:i386,` `libncurses5:i386`, and `libstdc++6:i386`: 

```
sudo dpkg --add-architecture i386
```

Or if you are using Ubuntu 12.04 LTS (Precise Pangolin) or below, use this: 

```
echo "foreign-architecture i386" > /etc/dpkg/dpkg.cfg.d/multiarch
```

Then:

```
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
```

After these steps, you should be able to run the 32-bit application:

```
./example32bitprogram
```

And also from

```
http://stackoverflow.com/questions/23498237/compile-program-for-32bit-on-64bit-linux-os-causes-fatal-error
```

To compile 32 bit binaries on 64 bit Linux version, you have to Install libx32gcc development package and 32 bit GNU C Library
try this:

```
sudo apt-get install libx32gcc-4.8-dev
```

and
```
sudo apt-get install libc6-dev-i386
```

#### Installing Motif and X11
Tried installing - but `qbeta/qcompiler` still does not compile `motif/X11` libs

```
sudo apt-get install libmotif-dev
sudo apt-get install libx11-dev:i386
```

Perhaps this is for 64-bit Linux - `:i386 seems` to install 32-bit versions of the libraries

```
sudo apt-get install libx11-dev:i386 libxt-dev:i386 libmotif-dev:i386 libxp-dev:i386
```

#### Implementing Beta for Mac OS
The text below is form the time where Mac-computers were running on an Intel x86 processor, and since is no longer the case, the text below is no longer relevant.

MBS was implemented for a number of OS's including the Mac before the processor was changed to be an Intel x86.
The compiler has modules for generating code for the x86 and the object code format used by the Mac - whether or not the it is correct regarding the object code format has to be confirmed.
So in principle it should be possible to assemble a compiler for Mac OS using existing modules. It still remains to be done;-)

There is an attempt to port to Intel-based Mac - a new machine type: `mac_ix86` and a directory `GENERATOR/MAC_IX86` has been made, but it is  incomplete.
Not clear if created by OLM or Henry Michael Lassen - but probably OLM, since it does not seem to be checked-in at SVN.
There are several mac-related machine types: `mac`, `ppcmac`, `macosx`.
Note that when compiling with `-t mac_ix86`, it seems that 'mac' matches `mac_ix86` - i.e. a match is found i a machine type like `mac` matches a prefix og e.g. `mac_ix86`.

There are MACHO modules - the object-file format of the Mac - however, there seems to be ppc dependent code in some of the files - e.g. `MACHOmachine.bet` and `MACOSXmacho.bet`.
`MAC_IX86` has a file `MAC_IX86macho` which is a modified copy of `MACOSXmacho.bet`.
