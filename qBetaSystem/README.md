This project contains a new experimental compiler and integrated
development environment for the qBeta language. 
In its current state it is quite
incomplete and unstable.

## Compiler

In directory `qbeta`.

The compiler does currently not catch all errors - i.e. some
errorneous programs will pass the compiler, and subesquent pand execution of it mail fail.

Compile `qbeta.bet`using the std. Beta compiler: 

```beta qbeta.bet```

Compilimg and executing a qBetaprogram: `qbeta foo.bet`.

## VM

A VM for qBeta interpreted by BETA and C.

## qenv

The new IDE.

Compile `qenv.bet` using std. BETA compiler:

```beta qenv```

Run: 

```qenv```

## BETAworld

A nested structure of folders containing qBeta modules


