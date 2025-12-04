The file

   runbeta-arm.c

is a version of runbeta.c for the the RaspberryPi 3 (PI 3) with an ARM processor.

It includes files in directory arm

   arm-09-cstartup.c
   armc-09-cstubs.c
   armc-start.S
   
   Hello_bc.c

The file 

   build-RP3.bat 

builds a boot image for PI 3 - output on arm/kernel.img

However, it curently does not run.

The arm-files are copied from part2/arm09 of the 'bare metal tutorial' from

http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/ 

As of today, we have not been able to run the files on the tutorial on our PI3. We have not been able to run the turial examples on our PI 3.  The tutorial is a couple of years old and for PI 1 and PI 2 - we may have to make changes for PI 3.

The file

     Hello_bc.c

is a C-file with the byte code of Hello.abeta hardcoded as an initailization of an array. This is to move the the byte code to the PI3 since we currently have no file system. We have to find a more general form.

The -C option for qcompiler generates such a file in addition to the binary BC-file. See README.txt


