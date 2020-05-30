MEMORY
{
   SRAM (rwx) : ORIGIN = 0, LENGTH = 32M	
}

SECTIONS
{
   .text :
   {
     KEEP (*(.traps))
     . = 0x100;      /* space for command line */
     *(.text .text.* .gnu.linkonce.t*)     
   }
   
   .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }

   .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) }
   PROVIDE_HIDDEN (__exidx_start = .);
   .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) }
   PROVIDE_HIDDEN (__exidx_end = .);

   .data : { *(.data .data.* .gnu.linkonce.d*) }

   .bss (NOLOAD): {
   __bss_start = ALIGN(0x10);
   *(.bss .bss.*)
   *(COMMON)

   __bss_end = ALIGN(0x10);
   
   . = ALIGN(0x10);
   . += 0x1000;
   __cpu0_stack_end = .;

   _end = .;
   }

}