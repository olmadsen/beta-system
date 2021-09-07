@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/MiniSystem/VM
echo %BL%

ls %BL%/arm/rpi.x %1 %BL%/runbeta-arm.c %BL%/arm/qbeta-clib.c  %BL%/arm/qbeta-slib.S  %BL%/arm/init_mmu.S

echo arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,%BL%/arm/rpi.x %1 %BL%/runbeta-arm.c %BL%/arm/qbeta-clib.c %BL%/arm/init_mmu.S -o kernel.elf

echo "   "
arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,%BL%/arm/rpi.x %1 %BL%/runbeta-arm.c %BL%/arm/qbeta-clib.c  %BL%/arm/qbeta-slib.S %BL%/arm/init_mmu.S -o kernel.elf


arm-none-eabi-objcopy kernel.elf -O binary kernel.img
