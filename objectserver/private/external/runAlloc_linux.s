## runAlloc_linux.s
## ================
## 
## Created by Soren Brandt and Jacob Seligmann.
## 
## Linux interface to BETA RTS allocation routines used by ObjectSerializer.
##
.data
.globl	_pReg1
.text
.globl _DoAlloVR1
_DoAlloVR1:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR1
      ret

.globl _DoAlloVR2
_DoAlloVR2:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR2
      ret

.globl _DoAlloVR4
_DoAlloVR4:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR4
      ret

.globl _DoAlloVR8
_DoAlloVR8:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloVR8
      ret

.globl _DoAlloRR
_DoAlloRR:
      movl 4(%esp),%edx  # obj to RegObj 
      movl 8(%esp),%eax  # offset to DataReg1 
      movl 12(%esp),%ebx # range to DataReg2 
      call AlloRR
      ret

.globl _DoAlloS
_DoAlloS:
      movl 4(%esp),%edi
      movl %edi,_pReg1   # origin to pReg1 
      movl 8(%esp),%edi  # proto to RegArg 
      call AlloS
      movl %edi,%eax     # result in RegArg 
      ret

.globl _DoAlloH
_DoAlloH:
      movl $0,_pReg1     # origin to pReg1 (unused) 
      movl 4(%esp),%edi  # proto to RegArg 
      call AlloH
      movl %edi,%eax     # Result in RegArg 
      ret
