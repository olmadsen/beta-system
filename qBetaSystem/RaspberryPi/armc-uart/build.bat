

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,rpi.x armc-uart.c ../../VM/arm/armc-09-cstubs.c  ../../VM/arm/armc-09-cstartup.c  ../../VM/arm/armc-09-start.S -o kernel.elf


arm-none-eabi-objcopy kernel.elf -O binary kernel.img
