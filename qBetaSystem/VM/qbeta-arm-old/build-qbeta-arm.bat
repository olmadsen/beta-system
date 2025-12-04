@ECHO OFF

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,rpi.x runbeta-arm.c qbeta-clib.c qbeta-slib.S init_mmu.S -o kernel.elf
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
