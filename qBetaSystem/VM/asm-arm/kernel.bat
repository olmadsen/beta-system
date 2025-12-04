arm-none-eabi-gcc -nostartfiles -o kernel.elf -Wl,-T,kernel.ld kernel.s
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
ls -lt
