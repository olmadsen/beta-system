	.SPACE $PRIVATE$
	.SUBSPA $DATA$,QUAD=1,ALIGN=8,ACCESS=31
	.SUBSPA $BSS$,QUAD=1,ALIGN=8,ACCESS=31,ZERO,SORT=82
	.SPACE $TEXT$
	.SUBSPA $LIT$,QUAD=0,ALIGN=8,ACCESS=44
	.SUBSPA $CODE$,QUAD=0,ALIGN=8,ACCESS=44,CODE_ONLY
	.IMPORT $global$,DATA
	.IMPORT $$dyncall,MILLICODE
; gcc_compiled.:
	.IMPORT printf,CODE
	.SPACE $TEXT$
	.SUBSPA $LIT$

	.align 4
L$C0000:
	.STRING "%d %d %d\x0a\x00"
	.SPACE $TEXT$
	.SUBSPA $CODE$

	.align 4
	.EXPORT myproc,CODE
	.EXPORT myproc,ENTRY,PRIV_LEV=3,ARGW0=GR,ARGW1=GR,ARGW2=GR,RTNVAL=GR
myproc:
	.PROC
	.CALLINFO FRAME=128,CALLS,SAVE_RP,SAVE_SP,ENTRY_GR=3
	.ENTRY
	stw %r2,-20(0,%r30)
	copy %r3,%r1
	copy %r30,%r3
	stwm %r1,128(0,%r30)
	stw %r26,-36(0,%r3)
	stw %r25,-40(0,%r3)
	stw %r24,-44(0,%r3)
	ldi 1,%r19
	stw %r19,-36(0,%r3)
	ldi 2,%r19
	stw %r19,-40(0,%r3)
	ldi 3,%r19
	stw %r19,-44(0,%r3)
	ldil L'L$C0000,%r19
	ldo R'L$C0000(%r19),%r26
	ldw -36(0,%r3),%r25
	ldw -40(0,%r3),%r24
	ldw -44(0,%r3),%r23
	.CALL ARGW0=GR,ARGW1=GR,ARGW2=GR,ARGW3=GR
	bl printf,%r2
	nop
L$0001:
	ldw -20(0,%r3),%r2
	ldo 64(%r3),%r30
	ldwm -64(0,%r30),%r3
	bv,n 0(%r2)
	.EXIT
	.PROCEND
