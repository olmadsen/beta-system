# Compiling and executing qBeta for RPI-Arm
This note describes how to compile and execute qBeta programs on a bare bone RPI-Arm procesor.

You must use the `qbeta` compiler and the `build-arm` script both placed in the `qBetaSystem/bin` directory.

Let `foo.qbeta` be a qbeta program placed in a directory by the name `foo`, and
you must be placed in this directory.

To compile `foo`use

````
qbeta -C foo
````
The `-C` switch makes the compiler generate a file `foo_bc.c` containing the byte code for `foo`.

To generate an image that can be loaed in the RPI-Arm use:
````
build foo_bc.c
````
This will generated the files `kernel7.elf` and `kernel7.img`.

You may download one of these to the RPI-Arm - which one depends on your RPI-Arm configuration.

In `qBetaSystem/workspace`ypu may find some examples of Arm programs - see directories`Arm*`.

In principles any qBeta program should be able to run on the RPI.

**However, as of today, the RPI-Arm implementation is incomplete**.
