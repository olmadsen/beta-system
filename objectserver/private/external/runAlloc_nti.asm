; runAlloc_nti.org
; ================
; 
; Created by Soren Brandt and Soren Pingel Dalsgaard.
; 
; NT-Intel interface to BETA RTS allocation routines used by ObjectSerializer.
;
.386P
ifdef ??version
smart
.model	flat
else
if @Version gt 510
.model	FLAT
else
_TEXT   SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT   ENDS
_DATA   SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS    ENDS
_TLS    SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS    ENDS
FLAT    GROUP _DATA, CONST, _BSS
ASSUME  CS: FLAT, DS: FLAT, SS: FLAT
endif
endif
extrn	AlloRR:proc
extrn	AlloS:proc
extrn	AlloH:proc
extrn	AlloVR1:proc
extrn	AlloVR2:proc
extrn	AlloVR4:proc
extrn	AlloVR8:proc
extrn	_pReg1:dword
_CODE	SEGMENT
public	_DoAlloVR1
_DoAlloVR1:
	mov	edx,4[esp]	; obj to RegObj
	mov	eax,8[esp]	; offset to DataReg1
	mov	ebx,12[esp]	; range to DataReg2
	call	AlloVR1
	ret

public	_DoAlloVR2
_DoAlloVR2:
	mov	edx,4[esp]	; obj to RegObj
	mov	eax,8[esp]	; offset to DataReg1
	mov	ebx,12[esp]	; range to DataReg2
	call	AlloVR2
	ret

public	_DoAlloVR4
_DoAlloVR4:
	mov	edx,4[esp]	; obj to RegObj
	mov	eax,8[esp]	; offset to DataReg1
	mov	ebx,12[esp]	; range to DataReg2
	call	AlloVR4
	ret

public	_DoAlloVR8
_DoAlloVR8:
	mov	edx,4[esp]	; obj to RegObj
	mov	eax,8[esp]	; offset to DataReg1
	mov	ebx,12[esp]	; range to DataReg2
	call	AlloVR8
	ret

public	_DoAlloRR
_DoAlloRR:
	mov	edx,4[esp]	; obj to RegObj
	mov	eax,8[esp]	; offset to DataReg1
	mov	ebx,12[esp]	; range to DataReg2
	call	AlloRR
	ret

public	_DoAlloS
_DoAlloS:
	mov	edi,4[esp]
	mov	_pReg1,edi	; origin to pReg1
	mov	edi,8[esp]	; proto to RegArg
	call	AlloS
	mov	eax,edi		; result in RegArg
	ret

public	_DoAlloH
_DoAlloH:
	mov	_pReg1,0	; origin to pReg1 (unused]
	mov	edi,4[esp]	; proto to RegArg
	call	AlloH
	mov	eax,edi		; Result in RegArg
	ret
_CODE	ENDS
	END

