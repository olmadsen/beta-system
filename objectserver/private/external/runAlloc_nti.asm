## runAlloc_nti.asm
## ================
## 
## Created by Soren Brandt and Soren Pingel Dalsgaard.
## 
## NT-Intel interface to BETA RTS allocation routines used by ObjectSerializer.
##
.data
.globl	_pReg1
.text
.globl _DoAlloVR1
_DoAlloVR1:
      mov edx, 4[esp]  /* obj to RegObj */
      mov eax, 8[esp]  /* offset to DataReg1 */
      mov ebx, 12[esp] /* range to DataReg2 */
      call AlloVR1
      ret

.globl _DoAlloVR2
_DoAlloVR2:
      mov edx, 4[esp]  /* obj to RegObj */
      mov eax, 8[esp]  /* offset to DataReg1 */
      mov ebx, 12[esp] /* range to DataReg2 */
      call AlloVR2
      ret

.globl _DoAlloVR4
_DoAlloVR4:
      mov edx, 4[esp]  /* obj to RegObj */
      mov eax, 8[esp]  /* offset to DataReg1 */
      mov ebx, 12[esp] /* range to DataReg2 */
      call AlloVR4
      ret

.globl _DoAlloVR8
_DoAlloVR8:
      mov edx, 4[esp]  /* obj to RegObj */
      mov eax, 8[esp]  /* offset to DataReg1 */
      mov ebx, 12[esp] /* range to DataReg2 */
      call AlloVR8
      ret

.globl _DoAlloRR
_DoAlloRR:
      mov edx, 4[esp]  /* obj to RegObj */
      mov eax, 8[esp]  /* offset to DataReg1 */
      mov ebx, 12[esp] /* range to DataReg2 */
      call AlloRR
      ret

.globl _DoAlloS
_DoAlloS:
      mov edi, 4[esp]
      mov _pReg1, edi  /* origin to pReg1 */
      mov edi, 8[esp]  /* proto to RegArg */
      call AlloS
      mov eax, edi     /* result in RegArg */
      ret

.globl _DoAlloH
_DoAlloH:
      mov _pReg1, 0   /* origin to pReg1 (unused] */
      mov edi, 4[esp] /* proto to RegArg */
      call AlloH
      mov eax, edi    /* Result in RegArg */
      ret
