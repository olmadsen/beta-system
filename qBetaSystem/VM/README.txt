Jürgen, see 2. To compile runbeta.c below
            =======================

1. General
==========
The file 

   interpreter_c.c 

is the interpreter for the virtual machine for qbeta.
It is written in C and may be compiled and linked with the qbeta compiler: 
called 'qcompiler'.

There is also an interpreter written in Beta.

A command

   qcompiler foo

will compile foo and execute using the interpreter written in Beta

A command 

   qcompiler -c foo

will use the interpreter written in C

A command

   qcompiler -c foo

will compile and generate a bytcode file

   foo..bc

and not execute the bytecode.

The file

   runbeta.c

includes the interpreter written in C.

A call 

   runbeta foo..BC

will execute the bytecode for foo

2. To compile runbeta.c     <<<<<<<<<<<<<<<<<<<< Jürgen, see here
=======================

On Windows/Cygwin:

   gcc -o runbeta runbeta.c

On Linux/Ubuntu:

   gcc -o runbeta runbeta.c -lpthread

The file

   TST..bc

contains byte code to the qbeta program TST and may be executed using:

   runbeta TST..bc

The result should be:

$ runbeta TST..bc
argc: 2
Runbeta: 2 TST..bc 349684 executing xbeta/qbeta
*** C interpreter - threadId:0

A:abcdefghijkl
B: abcdefghijklmnopqrstuvw
C:  abcdefghijklmnopqrstuvw
D:   abcdefghijkl
E:    abcdefghijklm
F:     abcdefgh.ghi?
G:      abcdefhijklm
H:       abcdefghijklmnop
I:        abcdefgh
J:         abcdefghijklmnopq
K:          abcdefghijklmnopqrstu
L:           abcdefghijklmnopqrst
M:            abcde
N:             abcdefghijklmnopqrstuvwxyz
O:              abcdefghijklmnopqrstuvwx
P:               abcdefghijklm
Q:                abcdefghijklmnopqrstuvwxyz
!
Stop: threadId: 0
   
