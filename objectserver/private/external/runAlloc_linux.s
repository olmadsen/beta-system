## runAlloclinux.s
## ================
## 
## Created by Soren Brandt and Jacob Seligmann.
## 
## Linux interface to BETA RTS allocation routines used by ObjectSerializer.
##
.data
.globl	pReg1
.text
.globl DoAlloVR1
DoAlloVR1:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR1
      ret

.globl DoAlloVR2
DoAlloVR2:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR2
      ret

.globl DoAlloVR4
DoAlloVR4:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR4
      ret

.globl DoAlloVR8
DoAlloVR8:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR8
      ret

.globl DoAlloRR
DoAlloRR:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloRR
      ret

.globl DoAlloS
DoAlloS:
      movl 4(%esp),%edi
      movl %edi,pReg1   # origin to pReg1 
      movl 8(%esp),%edi  # proto to RegArg 
      call AlloS
      movl %edi,%eax     # result in RegArg 
      ret

.globl DoAlloH
DoAlloH:
      movl $0,pReg1     # origin to pReg1 (unused) 
      movl 4(%esp),%edi  # proto to RegArg 
      call AlloH
      movl %edi,%eax     # Result in RegArg 
      ret
