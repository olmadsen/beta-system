.section ".text.startup"

.global _start
_start:

0:      wfe
        b 0b
