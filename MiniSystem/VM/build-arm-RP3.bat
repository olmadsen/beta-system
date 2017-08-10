@ECHO OFF

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,arm/rpi.x runbeta-arm.c arm/armc-09-cstubs.c arm/armc-09-cstartup.c arm/armc-09-start.S -o arm/kernel.elf
arm-none-eabi-objcopy arm/kernel.elf -O binary arm/kernel.img
