
Background Material
===================

It has proven notoriously difficult to locate all the different pieces of documentation needed for the
Broadcom BCM2837 SoC. This section collects all the many sources of documentation (and attempts) to provide
and overview.


The Raspberry 3 Model B Hardware
--------------------------------

### Broadcom BCM2837

Citing <https://www.raspberrypi.com/documentation/computers/processors.html#bcm2837>

> This is the Broadcom chip used in the Raspberry Pi 3 Model B, later models of the Raspberry Pi 2 Model B,
> and the Raspberry Pi Compute Module 3. The underlying architecture of the BCM2837 is identical to the
> BCM2836. The only significant difference is the replacement of the ARMv7 quad core cluster with a quad-core
> ARM Cortex A53 (ARMv8) cluster.
>
> The ARM cores run at 1.2GHz, making the device about 50% faster than the Raspberry Pi 2. The VideoCore IV
> runs at 400MHz.

This SoC comprises

 * an Arm Cortex A53 cluster (4 cores with 16 kB Level-1 instruction cache plus 16 kB Level-1 data cache
   each) with 512 kB shared Level-2 cache,
 * a Broadcom VideoCore IV 3D GPU (including a firmware PROM),
 * 128 kB VideoCore cache,
 * I/O Peripherals (GPIO, Timers/PWM, UARTs, SPIs, I^2C, USB, eMMC (SD Card interface), Analog & Digital
   Audio I/O, DMA)
 * Arm Control (see below)
 
The SoC is connected to an external 1024 MB SDRAM chip.

The RAM and I/O Peripherals are shared between the CPU and the GPU. The GPU is the master and orchestrates the
boot process. The Broadcom VideoCore IV 3D and the shared peripherals together are known under the designation
**BCM2710**. So, in effect, the BCM2837 == BCM2710 + one Arm Cortex A53 cluster. The BCM2708 (used for
Raspberry Pi 1), BCM2709 (Pi 2) and BCM2710 appear to be identical except some speed improvements, hence the
specifications and documentation of all of these chips (except for the Arm cores, cache size and additional
"Arm Control" module) are identical.


### Physical Memory Map (as seen from the Arm CPU)

| Start         | Description     |
| ------------- | --------------- |
| `0x40040000` | Unused area: `0x40040000-0xFFFFFFFF`   |
| `0x40030000` | Debug Access Port memory-mapped registers. See <https://developer.arm.com/documentation/ddi0500/j/Debug/Memory-mapped-register-summary>                         |
| `0x40020000` | Debug ROM. See <https://developer.arm.com/documentation/ddi0500/j/Debug/ROM-table/ROM-table-register-summary>                                     |
| `0x40000000` | Arm-local Peripherals: Timers, IRQs, Mailboxes. See <https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf>                   |
| `0x3F000000` | I/O Peripherals. See <https://datasheets.raspberrypi.com/bcm2835/bcm2835-peripherals.pdf> with errata: <https://elinux.org/BCM2835_datasheet_errata><br>Alternatively an edited revision adapted (partially) for BCM2837: <https://github.com/kshamko/gopherberry/blob/master/docs/BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf>    |
| `0x00000000` | SDRAM (1008 MB accessible by the CPU). Shared between CPU and GPU. Lower part is used for the CPU and upper part for GPU (that can also use the upper 16 MB which is not available to the CPU). The split is determined at boot time – see below  |

The lower 1 GB (`0x00000000 – 0x3FFFFFFF`) of this address space is managed by the BCM2710 part of the SoC,
while memory above `0x40000000` is internal to the Arm Core. Hence, the RAM available to the CPU cannot span
an entire 1 GB, because the address space must be shared with the memory-mapped peripherals, thus the upper 16
MB RAM is always reserved to the VideoCore.


### Arm Control

The Arm control is an addition to the original Raspberry Pi SoC core (BCM2708) in order to handle multiple CPU
cores as the BCM2735 was a single-core SoC. It offers:

 * A 64-bit timer
 * Routing of the various interrupts from the BCM2710 as well as internal Arm interrupts to the individual cores
 * Mailboxes between the processors
 * Extra interrupt timer

It is described in the <https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf> document.


### Arm Cortex A53 Cluster

A standard cluster of 4 Arm Cortex A53 cores running at 1.2 GHz according to the specs. The CPU is started by
the GPU after the 2nd bootloader stage is complete (kernel is loaded into RAM). The cores are reset into the
Supervisor (SVC) mode of EL3 and started from `0x0`. A setting in `config.txt` determines if the cores are
started in 64-bit (AArch64) or 32-bit (v7-A) mode. Note, that if the cores are started in 32-bit mode, it will
not be possible to enter 64-bit mode!

Documentation sources:

 * Arm-v8 Architecture Reference Manual \[**DDI 0487**]:\
   Contains all the generic information on the Arm-v8 family of CPUs. For details specific to the individual
   model, see the Technical Reference document instead (DDI 0500 below in our case).
    * HTML: N/A
    * PDF (huge - almost 9000 pages!): <https://developer.arm.com/documentation/ddi0487/latest/>
 * Arm-v7-A/R Architecture Reference \[**DDI 0406**]:\
   Only about 1/3 of the -v8 manual above, covering only the 32-bit elements
    * HTML: N/A
    * PDF (large - almost 3000 pages): <https://developer.arm.com/documentation/ddi0406/latest/>
 * Arm Cortex-A53 Technical Reference \[**DDI 0500**]:
    * HTML: <https://developer.arm.com/documentation/ddi0500/latest/>
    * PDF (623 pages): <https://documentation-service.arm.com/static/6040c321ee937942ba301626>
 * Arm Cortex-A series Programmer's Guide \[**DEN 0013**]:\
   Contains all the introductory material
    * HTML: <https://developer.arm.com/documentation/den0013/latest/>
    * PDF (421 pages): <https://documentation-service.arm.com/static/5ff5c9fd89a395015c28fc51>
 * AArch32 instruction set \[**DDI 0597**]:
    * HTML: <https://developer.arm.com/documentation/ddi0597/latest/>
    * PDF (large - over 2100 pages): <https://documentation-service.arm.com/static/63a0803f1d698c4dc521cd8b>
 * AArch32 Assembler User Guide \[**DUI 0473**]:\
   (Offers a better overview over the instruction set than DDI 0597)
    * HTML: <https://developer.arm.com/documentation/dui0473/latest/>
 * AArch64 instruction set \[**DDI 0602**]:
    * HTML: <https://developer.arm.com/documentation/ddi0602/latest/>
    * PDF (huge over 5100 pages): <https://documentation-service.arm.com/static/63a082ee3f28e5456434c6fd>
 * Arm Cortex-A53 MPCore Processor Advanced SIMD and Floating-point Extension \[**DDI 0502**]:
    * HTML: <https://developer.arm.com/documentation/ddi0502/latest/>
    * PDF (34 pages): <https://documentation-service.arm.com/static/5e907926c8052b16087615a6>
 * List of other useful documentation:
    * <https://developer.arm.com/documentation/ddi0500/j/Preface/About-this-book/Additional-reading>


### Broadcom VideoCore IV 3D GPU

Architecture Reference Guide: <https://docs.broadcom.com/doc/12358545>


### SDRAM: EDB8132B4PB-8D-F

 * 8 Gbit LPDDR2 SDRAM
 * <https://media-www.micron.com/-/media/client/global/documents/products/data-sheet/dram/mobile-dram/low-power-dram/lpddr2/168b_2e0e_embedded_lpddr2_sdram.pdf>


### External Peripherals

#### BCM43438

 * WiFi (802.11ac,b,g,n)
 * Bluetooth 4.1 (BR/EDR & Low Energy)
 * FM radio with RDS support (not connected to antenna on the Raspberry Pi)
 * <https://pdf1.alldatasheet.com/datasheet-pdf/view/1018493/CYPRESS/BCM43438.html>
 

#### SMSC LAN9514

 * USB 2.0 hub
 * 4 external ports
 * 10/100 Ethernet NIC
 * <https://www.microchip.com/en-us/product/LAN9514>
 

Bare-metal Startup Documentation and Examples
---------------------------------------------

 * Bare-metal Boot code for ARMv8-A Processors Application Note \[**DAI 0527**]:
    * HTML: N/A
    * PDF (53 pages): <https://developer.arm.com/documentation/dai0527/latest/>
 * Chapter 13 of Programmer's Guide DEN 0013 (see links above). Direct HTML link:
   <https://developer.arm.com/documentation/den0013/d/Boot-Code>
 * Armstubs source code (linked into the `start??.elf` files found in the boot section):
   <https://github.com/raspberrypi/tools/tree/master/armstubs> When "`kernel_old=1`" is *not* found in the
   `config.txt` file, one of these Armstubs will be loaded into `0x0` in order to start a Linux
   kernel. Details on this can be found on this page:
   <https://leiradel.github.io/2019/01/20/Raspberry-Pi-Stubs.html>
 * FOSDEM 2017 talk by Tristan Gingold
    * Slides: <https://archive.fosdem.org/2017/schedule/event/programming_rpi3/attachments/slides/1475/export/events/attachments/programming_rpi3/slides/1475/bare_metal_rpi3.pdf>
    * Source code: <https://github.com/gingold-adacore/rpi3-fosdem17>
 * Litmus Runner project from Cambridge. (AArch64 code)
    * <https://github.com/rems-project/system-litmus-harness/tree/2ac02cc743ccdb1221cc82dd6a871bc36357db11/firmware/bcm2837>
 * Android KVM AArch32 source code
    * <https://android-kvm.googlesource.com/linux/+/refs/heads/pkvm/arch/arm>
    * <https://android.googlesource.com/kernel/bcm/+/refs/heads/android-bcm-tetra-3.10-marshmallow-mr1-wear-release/arch/arm/>


The Raspberry Pi Bootloader Step-by-step
----------------------------------------

The boot process is governed by the VideoCore for the first two stages.

The repository containing the bootloader files mentioned below – including the Broadcom proprietary binaries
is here: <https://github.com/raspberrypi/firmware/tree/master/boot>

Documentation on the boot folder is here:
<https://www.raspberrypi.com/documentation/computers/configuration.html#boot-folder-contents>


### Stage 0 – locate bootcode.bin

 * The bootloader stage 0 is located in VideoCore ROM.
 * The VideoCore contains a group of 66 one-time-programmable registers (fuses). Bits may be changed from 0 to
   1 but can never be changed back to 0.
 * List of registers <https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#otp-registers>
 * Reading and changing the registers from Raspberry Pi OS:
   <https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#industrial-use-of-the-raspberry-pi>
 * Register 17 contains the Boot Mode settings
    * Default value is `0x1020000a`
      * F\_osc = 19.2 MHz (bit 1)
      * SDIO pull ups (bit 3)
      * Boot from SD card enabled (bit 21)
      * Boot from USB enabled (bit 28)
 * Follow the procedure in
   <https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#boot-sequence> to locate a
   `bootcode.bin` file containing the first bootloader stage.
 * The `bootcode.bin` file is loaded into the VideoCore cache (as the SDRAM has not yet been turned on and
   initialized)
   
   
### Stage 1 – load start??.elf

 * The stage 1 bootloader in `bootcode.bin` will search for the two files `autoboot.txt` and `config.txt`:
   <https://www.raspberrypi.com/documentation/computers/config_txt.html>. The latter contains a lot of
   settings related to peripheral – and in particular video – configuration.
 * The SDRAM is turned on and initialized.
 * Based on the settings in config.txt, the bootloader will select and load a pair of files (`fixup??.db`,
   `start??.elf`), which is the second stage bootloader. There are currently 4 pairs of these files,
   representing 4 GPU configurations
    * (no suffix): Normal GPU configuration. Used when none of the options below are selected in `config.txt`.
    * `_x`: Full GPU package including camera support and extra codecs. Will require a large GPU RAM
      allocation. Use `start_x=1` to enable this option.
    * `_db`: GPU debugging. Will require a bit extra RAM for the GPU. Use `start_debug=1` to enable this
      option.
    * `_cd`: Minimal GPU package. Set `gpu_mem=16` to enable this option.
    * The selected `start??.elf` file contains the actual bootloader code – and GPU drivers and codecs when
      selected.
    * The selected `fixup??.dat` file contains the GPU memory map.
    * <https://www.raspberrypi.com/documentation/computers/config_txt.html#boot-options>
    * <https://www.raspberrypi.com/documentation/computers/config_txt.html#memory-options>
 * The selected `start??.elf` file will be loaded into the top of SDRAM


### Stage 2 – load the kernel and start the Arm CPU

The second stage bootloader will

 * Initialize the GPU, install drivers/codecs etc.
 * Initialize peripherals according to the settings in `config.txt`
 * Select and load either `kernel7.img` (32-bit is the standard setting) or `kernel8.img` (AArch64 selected
   when `arm_64bit=1`). See <https://www.raspberrypi.com/documentation/computers/config_txt.html#arm_64bit>
 * The kernel file is loaded into the address given by `kernel_address`
   <https://www.raspberrypi.com/documentation/computers/config_txt.html#kernel_address> unless `kernel_old=1`
   is selected <https://www.raspberrypi.com/documentation/computers/config_txt.html#kernel_old> in which case
   the kernel file is loaded into `0x0`.
 * If `kernel_old=1 then`
    * The Arm core is started. All 4 cores will start executing the kernel file simultaneously in Supervisor (SVC) mode of EL3.
 * Else
    * a device tree is constructed in RAM based on the hardware, settings in `config.txt` and
      `commandline.txt`. Input is loaded from relevant `.dtb` files in the `/boot` folder (including the
      `/boot/overlays` subfolder)
    * The binary format of a device tree is specified here:
      <https://github.com/devicetree-org/devicetree-specification/releases/download/v0.4-rc1/devicetree-specification-v0.4-rc1.pdf>
    * An "armstub" is placed in `0x0` and the CPU is started. Armstub sources are found here:
      <https://github.com/raspberrypi/tools/tree/master/armstubs> and analysed here:
      <https://leiradel.github.io/2019/01/20/Raspberry-Pi-Stubs.html>. They are included in the `start??.elf`
      file and are copied into place when needed.
    * The armstub will
       * Initialize all 4 cores with caching and other minor things (cf the analysis
         <https://leiradel.github.io/2019/01/20/Raspberry-Pi-Stubs.html>)
       * Drop from EL3 to EL2 (hypervisor mode)
       * Put core 1,2,3 to sleep – to be awakened by writing the address they should jump to in the respective
         core's mailbox #3 (see <https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf> for
         details on how to do that).
       * Core 0 will jump to the kernel with the following arguments:
          * r0: 0
          * r1: MACH\_TYPE: the constant value 3138, which means "BCM2708". See
            <https://www.arm.linux.org.uk/developer/machines/>
          * r2: Pointer to the device tree constructed above
