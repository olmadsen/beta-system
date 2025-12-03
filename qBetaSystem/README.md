This project contains a new experimental compiler and integrated
development environment for the qBeta language. 
In its current state it is quite
incomplete and unstable.

** Compiler

In directory qbeta

Parser: does currently not catch all syntax errors - i.e. some
errorneous programs will pass the parser, and subesquent phaes may
fail.

Compile qbeta.bet using the std. BETA compiler
Call: qbeta foo.bet 

** VM

A  VM for qBeta interpreted by BETA and C.

** qenv

The new IDE

Compile qenv.bet using std. BETA compiler
Run: qenv

**BETAworld:

A nested structure of folders containing qBeta modules


