## runAlloclinux.s
## ================
## 
## Created by Soren Brandt and Jacob Seligmann.
## 
## Linux interface to BETA RTS allocation routines used by ObjectSerializer.
##
.data
.globl	_pReg1
.globl	_pReg2
.text
.globl _DoAlloVR1
_DoAlloVR1:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,_pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,_pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR1


.globl _DoAlloVR2
_DoAlloVR2:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,_pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,_pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR2

.globl _DoAlloVR4
_DoAlloVR4:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,_pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,_pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR4

.globl _DoAlloVR8
_DoAlloVR8:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,_pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,_pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR8

.globl _DoAlloRR
_DoAlloRR:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,_pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,_pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloRR

.globl _DoAlloS
_DoAlloS:
      movl 4(%esp),%edi
      movl %edi,_pReg1    # origin to pReg1 
      movl 8(%esp),%edi  # proto to RegCall
      call AlloS
      movl %edi,%eax     # result in RegCall 
      ret

.globl _DoAlloH
_DoAlloH:
      movl 4(%esp),%edi  # proto to RegCall
      call AlloH
      movl %edi,%eax     # Result in RegCall 
      ret
