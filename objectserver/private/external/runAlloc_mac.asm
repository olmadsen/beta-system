## runAlloc_mac.asm
## ================
## 
## Created by Soren Brandt.
## 
## Interface to BETA RTS allocation routines used by ObjectSerializer.
##

text

## void DoAlloVR1 (int obj, int offset, int range)
lalign 2
global _DoAlloVR1
_DoAlloVR1:
      mov.l 4(%sp),%a0  # obj to RegObj
      mov.l 8(%sp),%d0  # offset to DataRegA
      mov.l 12(%sp),%d1 # range to DataRegB
      jsr AlloVR1
      rts

## void DoAlloVR2 (int obj, int offset, int range)
lalign 2
global _DoAlloVR2
_DoAlloVR2:
      mov.l 4(%sp),%a0  # obj to RegObj
      mov.l 8(%sp),%d0  # offset to DataRegA
      mov.l 12(%sp),%d1 # range to DataRegB
      jsr AlloVR2
      rts

## void DoAlloVR4 (int obj, int offset, int range)
lalign 2
global _DoAlloVR4
_DoAlloVR4:
      mov.l 4(%sp),%a0  # obj to RegObj
      mov.l 8(%sp),%d0  # offset to DataRegA
      mov.l 12(%sp),%d1 # range to DataRegB
      jsr AlloVR4
      rts

## void DoAlloVR8 (int obj, int offset, int range)
lalign 2
global _DoAlloVR8
_DoAlloVR8:
      mov.l 8(%sp),%a0  # obj to RegObj
      mov.l 12(%sp),%d0 # offset to DataRegA
      mov.l 16(%sp),%d1 # range to DataRegB
      jsr AlloVR8
      rts

## void DoAlloRR (int obj, int offset, int range)
lalign 2
global _DoAlloRR
_DoAlloRR:
      mov.l 4(%sp),%a0  # obj to RegObj
      mov.l 8(%sp),%d0  # offset to DataRegA
      mov.l 12(%sp),%d1 # range to DataRegB
      jsr AlloRR
      rts

## int DoAlloS (int origin, int proto)
lalign 2
global _DoAlloS
_DoAlloS:
      mov.l 4(%sp),%d7   # origin in d7
      mov.l 8(%sp),%a1   # proto to RegArg
      jsr AlloS
      mov.l %a1,%d0      # result in a1
      rts

## int DoAlloH (int proto)
lalign 2
global _DoAlloH
_DoAlloH:
      mov.l 4(%sp),%a1  # ProtoType in a1
      mov.l &0,%d7      # Origin address in d7 (unused)
      jsr AlloH
      mov.l %a1,%d0     # Result in a1
      rts
