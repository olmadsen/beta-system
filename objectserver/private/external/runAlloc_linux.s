## runAlloclinux.s
## ================
## 
## Created by Soren Brandt and Jacob Seligmann.
## 
## Linux interface to BETA RTS allocation routines used by ObjectSerializer.
##
.data
.globl	pReg1
.globl	pReg2
.text
.globl DoAlloVR1
DoAlloVR1:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR1


.globl DoAlloVR2
DoAlloVR2:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR2

.globl DoAlloVR4
DoAlloVR4:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR4

.globl DoAlloVR8
DoAlloVR8:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloVR8

.globl DoAlloRR
DoAlloRR:
      movl 8(%esp),%edx  # offset to pReg1
      movl %edx,pReg1
      movl 12(%esp),%edx # range to pReg2 
      movl %edx,pReg2
      movl 4(%esp),%edx  # obj to RegObj 
      jmp AlloRR

.globl DoAlloS
DoAlloS:
      movl 4(%esp),%edi
      movl %edi,pReg1    # origin to pReg1 
      movl 8(%esp),%edi  # proto to RegCall
      call AlloS
      movl %edi,%eax     # result in RegCall 
      ret

.globl DoAlloH
DoAlloH:
      movl 4(%esp),%edi  # proto to RegCall
      call AlloH
      movl %edi,%eax     # Result in RegCall 
      ret
