This project contains a new experimental compiler and integrated
development environment for BETA. In its current state it is quite
incomplete and unstable.

Compiler
--------
In directory miniCompiler

Parser: does currently not catch all syntax errors - i.e. some
errorneous programs will pass the parser, and subesquent phaes may
fail.

Compile compiler.bet using the std. BETA compiler
Call: compiler foo.bet 

Checker: a number of semantic checks are nor performed , incluing
typechecking of assignments and enter/exit-lists

Code generator: ...

BETAvm: a new VM for BETA interpreted by BETA

minienv:
--------
The new IDE

Compile minienv.bet using std. BETA compiler
Run: minienv foo.bet

BETAworld:
---------
A nested structure of folders containing BETA modules
See the paper: Modularization and browsing and integrated design


