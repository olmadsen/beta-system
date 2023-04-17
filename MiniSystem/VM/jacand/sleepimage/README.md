
Sleep Image
===========

This folder contains a complete boot image to be loaded on a FAT32 formatted (first or only bootable partition
of an) SD card, intended to be used to boot a Raspberry Pi 3 into a state where all cores are asleep and
awaiting a debugger.

The set up and instructions how to use it is available on the [Confluence
page](https://confluence.alexandra.dk/display/NEBS/Raspberry+Pi+3+Model+B).

The current bootloader files to put on a Raspberry Pi boot image is available from the official
[boot files repository](https://github.com/raspberrypi/firmware/tree/master/boot).

In addition to files taken from the repository above, this folder contains two files:

 - `config.txt` which contains the bootloader instructions to use.
 - `kernel7.img` the actual sleep code, the source of which is in `../sleepimage-src`.

The sleep image can also be used as the base for a compiled qBeta VM: Just replace the `kernel7.img` file
containing the dummy sleep implementation by the VM build output.
