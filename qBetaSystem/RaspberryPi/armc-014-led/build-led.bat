

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,rpi.x armc-014-led.c armc-cstubs.c armc-cstartup.c armc-start.S rpi-armtimer.c rpi-aux.c rpi-gpio.c rpi-interrupts.c rpi-mailbox-interface.c rpi-mailbox.c rpi-systimer.c -o kernel.elf
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
