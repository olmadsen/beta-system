This reposotory contains **The Mjølner Beta System**, which consits of a compiler Beta, a library of Beta patterns,a and and SDE.

In addition it contains **The qBeta System,** which consists of a compiler for qbeta, a library of qBeta objects and an SDE for qBeta.

Beta was developed by Bent Bruun Kristensen, Ole Lehrmann Madsen, Birger Møller-Pedersen and Kristen Nygaard. Here are some references:
1. B.B. Kristensen, O.L Madsen, B. Møller-Pedersen, K. Nygaard, Abstraction Mechanisms in the Beta Peogramming Language, POPL 1983.
2. O.L Madsen, B. Møller-Pedersen, K. Nygaard, Object-oriented Programmin in the ebta Programming language, ACM,Addison Wesley, 1993. Out of print, but a PDF-file is available in this repository.
3. B. B. Kristensen, O.L Madsen, B. Møller-Pedersen, The When, Why and ... , ACM/SIPGPLAN Conference on History of Programming languages, San Diego, 2007.

The MJølner Beta System was originally developed as part of the Nordic Mjølner Project and afterwards by Mjølner Informatics LtD. and Aarhs University.  The following people took part in the development, Peter Andersen, Lars Bak, Jørgen Lindskov Knudsen, Ole Lehrmann Madsen, Claus Nørgard, Elmer Sandvad, +++ to be completed.

qBeta is a relatively new language developed by Ole Lehrmann Madsen and derived from Beta. Birger Møller-Pedersen has (and is) an importat contributor and Henry Michael Lassen is a key person in the development of the SDE.

# Installing The Mjølner Beta System
In this Section, we describe how to install The Mjølner Beta System (MBS) from GitHub.
The Beta System is currently running on Windows 11 and Ubuntu-32.
Attempts have been made to make Beta run on Ubuntu-64 and MacOs, but so far this has not succeeded.

To gain access to the GitHub repostpry, mail to ```olm@cs.au.dk``` to be added as a collaborator.
We plan to make the repository public.

R5.5 is the newest version of MBS.

It is recommended to place beta in ```C:/beta/r5.5```:

```
cd c:
mkdir beta
cd beta
```

To checkout the system do this:

```
git clone git@github.com:olmadsen/beta-system.git r5.5
```

This will create a local copy of the repository (called ```r5.5```) on your machine.

You can ```git status, git diff, git add, git commit```, etc. relative to this local repository.

To propagate your changes to the official github repository use ```git push.``` To get contributions from others from the github repository to your own repository use ```git pull```.

## About the postwimp library
The postwimp library is currently a separate repository on github.
To check it out separately you use

```
git clone git@github.com:olmadsen/beta-postwimp.git postwimp
```

You will most likely want to use it inside a beta-system clone (e.g. ```r5.5``` (as above). 
For this reason, postwimp has been added as a submodule to beta-system. So inside your ```r5.5``` clone, you can activate the submodule as suh:

```
cd postwimp
it submodule init
git submodule update
```

You will then get the postwimp directory populated with the files, with changes separately tracked against the beta-postwimp.git repository.

If you are checking out the entire beta system, and would like to check out postwimp together with the rest, you can do it as such:

```
git clone --recurse-submodules git@github.com:olmadsen/beta-system.git r5.5
```

## MBS on Windows

### Required Software

The Beta System uses some other software packages:

Microsoft Visual Studio .NET 2003

if you don't have access to VS2003, you may contact olm@cs.au.dk or Peter.andersen@alexandra.dk for help.

VS2003 can also be downloaded from the internet, only a selection of them are required.
E.g. from ```http://download.cnet.com/Microsoft-Visual-Studio-NET-2003-Service-Pack-1/3000-10250_4-10729888.html```.
30-08-2023  VS2003 is now included as a ZIP file in the setup directory in the root of the GIT checkout, see below.

### Using VS2003 linker

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

**Ignore case while completing**

```
set completion-ignore-case on
```

You may want to add the following to your ```C:/cygwin64/home/<username>/.bashrc```

**Set cygwin window size to 100 chars wide, 60 lines high**

```
echo -en "\e[8;60;100t";
```
Setup of environment variables for cygwin
30-08-2023 The following complete setup works in newest cygwin 64 bit on Windows 11. Add to your C:/cygwin64/home/<username>/.bashrc

### Set up BETA environment

```
echo Setting up BETA r5.5
export BETALIB="c:/beta/r5.5"
export BETAOPTS="-s 38"
export MIASDK="ms"
```
 
### Set up PATH to include BETA binaries and administrative scripts (without using wrappers)

```
export CYGBETA=`cygpath $BETALIB` # for use in cygwin paths
export PATH="$CYGBETA/bin/nti_ms:$CYGBETA/bin/admin:${PATH}"
```
 
### Add Visual Studio 2003 to INCLUDE, PATH and LIB environment variables

```
export INCLUDE="c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Include/;c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include/;$INCLUDE"
export PATH="/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/SDK/v1.1/Bin:/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Bin/:/cygdrive/c/Program Files/Microsoft Visual Studio .NET 2003/Common7/IDE/:$PATH"
export LIB="c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/Lib/;c:/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Lib;$LIB"
```

### Set prompt to display BETA info, username, directory

```
PS1="\n[r5.5-$MIASDK]\n\[\033]0;\w\007\033[32m\]$USER@\h \[\033[33m\w\033[0m\]\n$ "
cd $BETALIB
```

???
 Original text - slightly different for VS2003 setup...


### Compiling Beta programs

A Beta program in the file ```foo.bet``` may be compiled by executing

```beta foo```

# Installing The qBeta System

* The qBeta System is currenlty in the folder MiniSystem - plans to rename to qBetaSystem
* QBS is part of MBS, so if you check-out MBS, you also have QBS.
* You must also install Cygwin as described above
* You don't need VS2003
* You must setup BETALIb as desribed above.

# Further notes on The Mjølner Beta System
In this Section, we mention further issues regarding MBS, but most of the stuff is probaly not relevant for most users of MBS.

### Running mbs_boot

Do we need to include this section?
