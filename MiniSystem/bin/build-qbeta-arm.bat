@ECHO OFF

echo %BETALIB%
set BL=%BETALIB%/MiniSystem/VM
set BLA=%BL%/qb-arm
echo %BL%

ls %1 %BLA%/rpi.x %BL%/runbeta-arm.c %BLA%/qbeta-clib.c  %BLA%/qbeta-slib.S  %BLA%/init_mmuL.S

echo arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,%BLA%/rpi.x %1 %BL%/runbeta-arm.c %BLA%/qbeta-clib.c %BLA%/qbeta-slib.S %BLA%/init_mmuL.S -o kernel.elf

arm-none-eabi-gcc -O0 -DRPI3 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv8-a -mtune=cortex-a53 -nostartfiles -g -Wl,-T,%BLA%/rpi.x %1 %BL%/runbeta-arm.c %BLA%/qbeta-clib.c %BLA%/qbeta-slib.S %BLA%/init_mmuL.S -o kernel.elf

echo    

arm-none-eabi-objcopy -v kernel.elf -O binary kernel.img
