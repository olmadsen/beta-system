@ECHO OFF

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,rpi.x armc-09.c armc-09-cstubs.c armc-09-cstartup.c armc-09-start.S -o kernel.elf
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
