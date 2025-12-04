

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,rpi.x armc-uart.c crt0.S  -o kernel.elf


arm-none-eabi-objcopy kernel.elf -O binary kernel.img
