
kernel.elf:     file format elf32-littlearm


Disassembly of section .text:

00008000 <_start>:
    8000:	e3a0d301 	mov	sp, #67108864	; 0x4000000
    8004:	ea00007a 	b	81f4 <_cstartup>

00008008 <_inf_loop>:
    8008:	eafffffe 	b	8008 <_inf_loop>

0000800c <kernel_main>:
    800c:	e92d4800 	push	{fp, lr}
    8010:	e28db004 	add	fp, sp, #4
    8014:	e24dd018 	sub	sp, sp, #24
    8018:	e50b0010 	str	r0, [fp, #-16]
    801c:	e50b1014 	str	r1, [fp, #-20]	; 0xffffffec
    8020:	e50b2018 	str	r2, [fp, #-24]	; 0xffffffe8
    8024:	e3083bb0 	movw	r3, #35760	; 0x8bb0
    8028:	e3403000 	movt	r3, #0
    802c:	e5933000 	ldr	r3, [r3]
    8030:	e2832010 	add	r2, r3, #16
    8034:	e3083bb0 	movw	r3, #35760	; 0x8bb0
    8038:	e3403000 	movt	r3, #0
    803c:	e5933000 	ldr	r3, [r3]
    8040:	e2833010 	add	r3, r3, #16
    8044:	e5933000 	ldr	r3, [r3]
    8048:	e3833602 	orr	r3, r3, #2097152	; 0x200000
    804c:	e5823000 	str	r3, [r2]
    8050:	e3a00a01 	mov	r0, #4096	; 0x1000
    8054:	fa000081 	blx	8260 <malloc>
    8058:	e1a03000 	mov	r3, r0
    805c:	e50b300c 	str	r3, [fp, #-12]
    8060:	e51b300c 	ldr	r3, [fp, #-12]
    8064:	e3530000 	cmp	r3, #0
    8068:	1a000006 	bne	8088 <kernel_main+0x7c>
    806c:	e3083bb0 	movw	r3, #35760	; 0x8bb0
    8070:	e3403000 	movt	r3, #0
    8074:	e5933000 	ldr	r3, [r3]
    8078:	e283302c 	add	r3, r3, #44	; 0x2c
    807c:	e3a02902 	mov	r2, #32768	; 0x8000
    8080:	e5832000 	str	r2, [r3]
    8084:	eafffff8 	b	806c <kernel_main+0x60>
    8088:	e3a03000 	mov	r3, #0
    808c:	e50b3008 	str	r3, [fp, #-8]
    8090:	ea000008 	b	80b8 <kernel_main+0xac>
    8094:	e51b3008 	ldr	r3, [fp, #-8]
    8098:	e1a03103 	lsl	r3, r3, #2
    809c:	e51b200c 	ldr	r2, [fp, #-12]
    80a0:	e0823003 	add	r3, r2, r3
    80a4:	e3a02000 	mov	r2, #0
    80a8:	e5832000 	str	r2, [r3]
    80ac:	e51b3008 	ldr	r3, [fp, #-8]
    80b0:	e2833001 	add	r3, r3, #1
    80b4:	e50b3008 	str	r3, [fp, #-8]
    80b8:	e51b3008 	ldr	r3, [fp, #-8]
    80bc:	e3530b01 	cmp	r3, #1024	; 0x400
    80c0:	bafffff3 	blt	8094 <kernel_main+0x88>
    80c4:	e3083bb0 	movw	r3, #35760	; 0x8bb0
    80c8:	e3403000 	movt	r3, #0
    80cc:	e5933000 	ldr	r3, [r3]
    80d0:	e283302c 	add	r3, r3, #44	; 0x2c
    80d4:	e3a02902 	mov	r2, #32768	; 0x8000
    80d8:	e5832000 	str	r2, [r3]
    80dc:	e51b300c 	ldr	r3, [fp, #-12]
    80e0:	e3a02000 	mov	r2, #0
    80e4:	e5832000 	str	r2, [r3]
    80e8:	ea000004 	b	8100 <kernel_main+0xf4>
    80ec:	e51b300c 	ldr	r3, [fp, #-12]
    80f0:	e5933000 	ldr	r3, [r3]
    80f4:	e2832001 	add	r2, r3, #1
    80f8:	e51b300c 	ldr	r3, [fp, #-12]
    80fc:	e5832000 	str	r2, [r3]
    8100:	e51b300c 	ldr	r3, [fp, #-12]
    8104:	e5932000 	ldr	r2, [r3]
    8108:	e30a311f 	movw	r3, #41247	; 0xa11f
    810c:	e3403007 	movt	r3, #7
    8110:	e1520003 	cmp	r2, r3
    8114:	9afffff4 	bls	80ec <kernel_main+0xe0>
    8118:	e3083bb0 	movw	r3, #35760	; 0x8bb0
    811c:	e3403000 	movt	r3, #0
    8120:	e5933000 	ldr	r3, [r3]
    8124:	e2833020 	add	r3, r3, #32
    8128:	e3a02902 	mov	r2, #32768	; 0x8000
    812c:	e5832000 	str	r2, [r3]
    8130:	e51b300c 	ldr	r3, [fp, #-12]
    8134:	e2833004 	add	r3, r3, #4
    8138:	e3a02000 	mov	r2, #0
    813c:	e5832000 	str	r2, [r3]
    8140:	ea000004 	b	8158 <kernel_main+0x14c>
    8144:	e51b300c 	ldr	r3, [fp, #-12]
    8148:	e2833004 	add	r3, r3, #4
    814c:	e5932000 	ldr	r2, [r3]
    8150:	e2822001 	add	r2, r2, #1
    8154:	e5832000 	str	r2, [r3]
    8158:	e51b300c 	ldr	r3, [fp, #-12]
    815c:	e2833004 	add	r3, r3, #4
    8160:	e5932000 	ldr	r2, [r3]
    8164:	e30a311f 	movw	r3, #41247	; 0xa11f
    8168:	e3403007 	movt	r3, #7
    816c:	e1520003 	cmp	r2, r3
    8170:	9afffff3 	bls	8144 <kernel_main+0x138>
    8174:	eaffffd2 	b	80c4 <kernel_main+0xb8>

00008178 <_sbrk>:
    8178:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
    817c:	e28db000 	add	fp, sp, #0
    8180:	e24dd014 	sub	sp, sp, #20
    8184:	e50b0010 	str	r0, [fp, #-16]
    8188:	e30933f0 	movw	r3, #37872	; 0x93f0
    818c:	e3403000 	movt	r3, #0
    8190:	e5933000 	ldr	r3, [r3]
    8194:	e3530000 	cmp	r3, #0
    8198:	1a000004 	bne	81b0 <_sbrk+0x38>
    819c:	e30933f0 	movw	r3, #37872	; 0x93f0
    81a0:	e3403000 	movt	r3, #0
    81a4:	e3092450 	movw	r2, #37968	; 0x9450
    81a8:	e3402000 	movt	r2, #0
    81ac:	e5832000 	str	r2, [r3]
    81b0:	e30933f0 	movw	r3, #37872	; 0x93f0
    81b4:	e3403000 	movt	r3, #0
    81b8:	e5933000 	ldr	r3, [r3]
    81bc:	e50b3008 	str	r3, [fp, #-8]
    81c0:	e30933f0 	movw	r3, #37872	; 0x93f0
    81c4:	e3403000 	movt	r3, #0
    81c8:	e5932000 	ldr	r2, [r3]
    81cc:	e51b3010 	ldr	r3, [fp, #-16]
    81d0:	e0822003 	add	r2, r2, r3
    81d4:	e30933f0 	movw	r3, #37872	; 0x93f0
    81d8:	e3403000 	movt	r3, #0
    81dc:	e5832000 	str	r2, [r3]
    81e0:	e51b3008 	ldr	r3, [fp, #-8]
    81e4:	e1a00003 	mov	r0, r3
    81e8:	e28bd000 	add	sp, fp, #0
    81ec:	e49db004 	pop	{fp}		; (ldr fp, [sp], #4)
    81f0:	e12fff1e 	bx	lr

000081f4 <_cstartup>:
    81f4:	e92d4800 	push	{fp, lr}
    81f8:	e28db004 	add	fp, sp, #4
    81fc:	e24dd018 	sub	sp, sp, #24
    8200:	e50b0010 	str	r0, [fp, #-16]
    8204:	e50b1014 	str	r1, [fp, #-20]	; 0xffffffec
    8208:	e50b2018 	str	r2, [fp, #-24]	; 0xffffffe8
    820c:	e30933f0 	movw	r3, #37872	; 0x93f0
    8210:	e3403000 	movt	r3, #0
    8214:	e50b3008 	str	r3, [fp, #-8]
    8218:	e3093450 	movw	r3, #37968	; 0x9450
    821c:	e3403000 	movt	r3, #0
    8220:	e50b300c 	str	r3, [fp, #-12]
    8224:	ea000004 	b	823c <_cstartup+0x48>
    8228:	e51b3008 	ldr	r3, [fp, #-8]
    822c:	e2832004 	add	r2, r3, #4
    8230:	e50b2008 	str	r2, [fp, #-8]
    8234:	e3a02000 	mov	r2, #0
    8238:	e5832000 	str	r2, [r3]
    823c:	e51b2008 	ldr	r2, [fp, #-8]
    8240:	e51b300c 	ldr	r3, [fp, #-12]
    8244:	e1520003 	cmp	r2, r3
    8248:	3afffff6 	bcc	8228 <_cstartup+0x34>
    824c:	e51b2018 	ldr	r2, [fp, #-24]	; 0xffffffe8
    8250:	e51b1014 	ldr	r1, [fp, #-20]	; 0xffffffec
    8254:	e51b0010 	ldr	r0, [fp, #-16]
    8258:	ebffff6b 	bl	800c <kernel_main>
    825c:	eafffffe 	b	825c <_cstartup+0x68>

00008260 <malloc>:
    8260:	f648 73c4 	movw	r3, #36804	; 0x8fc4
    8264:	f2c0 0300 	movt	r3, #0
    8268:	4601      	mov	r1, r0
    826a:	6818      	ldr	r0, [r3, #0]
    826c:	f000 b808 	b.w	8280 <_malloc_r>

00008270 <free>:
    8270:	f648 73c4 	movw	r3, #36804	; 0x8fc4
    8274:	f2c0 0300 	movt	r3, #0
    8278:	4601      	mov	r1, r0
    827a:	6818      	ldr	r0, [r3, #0]
    827c:	f000 bb3c 	b.w	88f8 <_free_r>

00008280 <_malloc_r>:
    8280:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
    8284:	f101 050b 	add.w	r5, r1, #11
    8288:	2d16      	cmp	r5, #22
    828a:	b083      	sub	sp, #12
    828c:	4606      	mov	r6, r0
    828e:	f240 80a7 	bls.w	83e0 <_malloc_r+0x160>
    8292:	f025 0507 	bic.w	r5, r5, #7
    8296:	42a9      	cmp	r1, r5
    8298:	bf94      	ite	ls
    829a:	2100      	movls	r1, #0
    829c:	2101      	movhi	r1, #1
    829e:	ea51 73d5 	orrs.w	r3, r1, r5, lsr #31
    82a2:	f040 80c4 	bne.w	842e <_malloc_r+0x1ae>
    82a6:	f000 fab1 	bl	880c <__malloc_lock>
    82aa:	f5b5 7ffc 	cmp.w	r5, #504	; 0x1f8
    82ae:	f0c0 82a7 	bcc.w	8800 <_malloc_r+0x580>
    82b2:	0a6b      	lsrs	r3, r5, #9
    82b4:	f000 80c2 	beq.w	843c <_malloc_r+0x1bc>
    82b8:	2b04      	cmp	r3, #4
    82ba:	f200 8141 	bhi.w	8540 <_malloc_r+0x2c0>
    82be:	09ab      	lsrs	r3, r5, #6
    82c0:	f103 0439 	add.w	r4, r3, #57	; 0x39
    82c4:	f103 0e38 	add.w	lr, r3, #56	; 0x38
    82c8:	00e3      	lsls	r3, r4, #3
    82ca:	f648 37b4 	movw	r7, #35764	; 0x8bb4
    82ce:	f2c0 0700 	movt	r7, #0
    82d2:	443b      	add	r3, r7
    82d4:	f1a3 0008 	sub.w	r0, r3, #8
    82d8:	685b      	ldr	r3, [r3, #4]
    82da:	4298      	cmp	r0, r3
    82dc:	d106      	bne.n	82ec <_malloc_r+0x6c>
    82de:	e00c      	b.n	82fa <_malloc_r+0x7a>
    82e0:	2900      	cmp	r1, #0
    82e2:	f280 80b1 	bge.w	8448 <_malloc_r+0x1c8>
    82e6:	68db      	ldr	r3, [r3, #12]
    82e8:	4298      	cmp	r0, r3
    82ea:	d006      	beq.n	82fa <_malloc_r+0x7a>
    82ec:	685a      	ldr	r2, [r3, #4]
    82ee:	f022 0203 	bic.w	r2, r2, #3
    82f2:	1b51      	subs	r1, r2, r5
    82f4:	290f      	cmp	r1, #15
    82f6:	ddf3      	ble.n	82e0 <_malloc_r+0x60>
    82f8:	4674      	mov	r4, lr
    82fa:	f8d7 c010 	ldr.w	ip, [r7, #16]
    82fe:	f8df e508 	ldr.w	lr, [pc, #1288]	; 8808 <_malloc_r+0x588>
    8302:	45f4      	cmp	ip, lr
    8304:	bf08      	it	eq
    8306:	687b      	ldreq	r3, [r7, #4]
    8308:	d027      	beq.n	835a <_malloc_r+0xda>
    830a:	f8dc 3004 	ldr.w	r3, [ip, #4]
    830e:	f023 0303 	bic.w	r3, r3, #3
    8312:	1b5a      	subs	r2, r3, r5
    8314:	2a0f      	cmp	r2, #15
    8316:	f300 8143 	bgt.w	85a0 <_malloc_r+0x320>
    831a:	2a00      	cmp	r2, #0
    831c:	f8c7 e014 	str.w	lr, [r7, #20]
    8320:	f8c7 e010 	str.w	lr, [r7, #16]
    8324:	f280 80a2 	bge.w	846c <_malloc_r+0x1ec>
    8328:	f5b3 7f00 	cmp.w	r3, #512	; 0x200
    832c:	f080 8114 	bcs.w	8558 <_malloc_r+0x2d8>
    8330:	08d9      	lsrs	r1, r3, #3
    8332:	2301      	movs	r3, #1
    8334:	18c8      	adds	r0, r1, r3
    8336:	687a      	ldr	r2, [r7, #4]
    8338:	1089      	asrs	r1, r1, #2
    833a:	408b      	lsls	r3, r1
    833c:	f857 1030 	ldr.w	r1, [r7, r0, lsl #3]
    8340:	4313      	orrs	r3, r2
    8342:	eb07 02c0 	add.w	r2, r7, r0, lsl #3
    8346:	607b      	str	r3, [r7, #4]
    8348:	3a08      	subs	r2, #8
    834a:	f8cc 1008 	str.w	r1, [ip, #8]
    834e:	f8cc 200c 	str.w	r2, [ip, #12]
    8352:	f847 c030 	str.w	ip, [r7, r0, lsl #3]
    8356:	f8c1 c00c 	str.w	ip, [r1, #12]
    835a:	10a2      	asrs	r2, r4, #2
    835c:	2001      	movs	r0, #1
    835e:	4090      	lsls	r0, r2
    8360:	4298      	cmp	r0, r3
    8362:	f200 8091 	bhi.w	8488 <_malloc_r+0x208>
    8366:	4218      	tst	r0, r3
    8368:	d105      	bne.n	8376 <_malloc_r+0xf6>
    836a:	f024 0403 	bic.w	r4, r4, #3
    836e:	0040      	lsls	r0, r0, #1
    8370:	3404      	adds	r4, #4
    8372:	4218      	tst	r0, r3
    8374:	d0fb      	beq.n	836e <_malloc_r+0xee>
    8376:	eb07 09c4 	add.w	r9, r7, r4, lsl #3
    837a:	46a0      	mov	r8, r4
    837c:	46cc      	mov	ip, r9
    837e:	f8dc 300c 	ldr.w	r3, [ip, #12]
    8382:	459c      	cmp	ip, r3
    8384:	d107      	bne.n	8396 <_malloc_r+0x116>
    8386:	e122      	b.n	85ce <_malloc_r+0x34e>
    8388:	2a00      	cmp	r2, #0
    838a:	f280 8130 	bge.w	85ee <_malloc_r+0x36e>
    838e:	68db      	ldr	r3, [r3, #12]
    8390:	459c      	cmp	ip, r3
    8392:	f000 811c 	beq.w	85ce <_malloc_r+0x34e>
    8396:	6859      	ldr	r1, [r3, #4]
    8398:	f021 0103 	bic.w	r1, r1, #3
    839c:	1b4a      	subs	r2, r1, r5
    839e:	2a0f      	cmp	r2, #15
    83a0:	ddf2      	ble.n	8388 <_malloc_r+0x108>
    83a2:	68dc      	ldr	r4, [r3, #12]
    83a4:	eb03 0c05 	add.w	ip, r3, r5
    83a8:	f8d3 8008 	ldr.w	r8, [r3, #8]
    83ac:	f045 0501 	orr.w	r5, r5, #1
    83b0:	4630      	mov	r0, r6
    83b2:	605d      	str	r5, [r3, #4]
    83b4:	f042 0501 	orr.w	r5, r2, #1
    83b8:	f8c8 400c 	str.w	r4, [r8, #12]
    83bc:	f8c4 8008 	str.w	r8, [r4, #8]
    83c0:	f103 0408 	add.w	r4, r3, #8
    83c4:	f8c7 c014 	str.w	ip, [r7, #20]
    83c8:	f8c7 c010 	str.w	ip, [r7, #16]
    83cc:	f8cc e00c 	str.w	lr, [ip, #12]
    83d0:	f8cc e008 	str.w	lr, [ip, #8]
    83d4:	f8cc 5004 	str.w	r5, [ip, #4]
    83d8:	505a      	str	r2, [r3, r1]
    83da:	f000 fa1d 	bl	8818 <__malloc_unlock>
    83de:	e022      	b.n	8426 <_malloc_r+0x1a6>
    83e0:	2910      	cmp	r1, #16
    83e2:	d824      	bhi.n	842e <_malloc_r+0x1ae>
    83e4:	f000 fa12 	bl	880c <__malloc_lock>
    83e8:	2510      	movs	r5, #16
    83ea:	2218      	movs	r2, #24
    83ec:	2402      	movs	r4, #2
    83ee:	f648 37b4 	movw	r7, #35764	; 0x8bb4
    83f2:	f2c0 0700 	movt	r7, #0
    83f6:	443a      	add	r2, r7
    83f8:	f1a2 0108 	sub.w	r1, r2, #8
    83fc:	6853      	ldr	r3, [r2, #4]
    83fe:	428b      	cmp	r3, r1
    8400:	f000 80ee 	beq.w	85e0 <_malloc_r+0x360>
    8404:	685a      	ldr	r2, [r3, #4]
    8406:	f103 0408 	add.w	r4, r3, #8
    840a:	68d9      	ldr	r1, [r3, #12]
    840c:	4630      	mov	r0, r6
    840e:	f022 0203 	bic.w	r2, r2, #3
    8412:	689d      	ldr	r5, [r3, #8]
    8414:	4413      	add	r3, r2
    8416:	685a      	ldr	r2, [r3, #4]
    8418:	60e9      	str	r1, [r5, #12]
    841a:	f042 0201 	orr.w	r2, r2, #1
    841e:	608d      	str	r5, [r1, #8]
    8420:	605a      	str	r2, [r3, #4]
    8422:	f000 f9f9 	bl	8818 <__malloc_unlock>
    8426:	4620      	mov	r0, r4
    8428:	b003      	add	sp, #12
    842a:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    842e:	2400      	movs	r4, #0
    8430:	230c      	movs	r3, #12
    8432:	4620      	mov	r0, r4
    8434:	6033      	str	r3, [r6, #0]
    8436:	b003      	add	sp, #12
    8438:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    843c:	f44f 7300 	mov.w	r3, #512	; 0x200
    8440:	2440      	movs	r4, #64	; 0x40
    8442:	f04f 0e3f 	mov.w	lr, #63	; 0x3f
    8446:	e740      	b.n	82ca <_malloc_r+0x4a>
    8448:	441a      	add	r2, r3
    844a:	68dd      	ldr	r5, [r3, #12]
    844c:	689f      	ldr	r7, [r3, #8]
    844e:	4630      	mov	r0, r6
    8450:	6851      	ldr	r1, [r2, #4]
    8452:	f103 0408 	add.w	r4, r3, #8
    8456:	60fd      	str	r5, [r7, #12]
    8458:	f041 0101 	orr.w	r1, r1, #1
    845c:	60af      	str	r7, [r5, #8]
    845e:	6051      	str	r1, [r2, #4]
    8460:	f000 f9da 	bl	8818 <__malloc_unlock>
    8464:	4620      	mov	r0, r4
    8466:	b003      	add	sp, #12
    8468:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    846c:	4463      	add	r3, ip
    846e:	4630      	mov	r0, r6
    8470:	f10c 0408 	add.w	r4, ip, #8
    8474:	685a      	ldr	r2, [r3, #4]
    8476:	f042 0201 	orr.w	r2, r2, #1
    847a:	605a      	str	r2, [r3, #4]
    847c:	f000 f9cc 	bl	8818 <__malloc_unlock>
    8480:	4620      	mov	r0, r4
    8482:	b003      	add	sp, #12
    8484:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    8488:	68bc      	ldr	r4, [r7, #8]
    848a:	6863      	ldr	r3, [r4, #4]
    848c:	f023 0903 	bic.w	r9, r3, #3
    8490:	eba9 0205 	sub.w	r2, r9, r5
    8494:	2a0f      	cmp	r2, #15
    8496:	bfcc      	ite	gt
    8498:	2300      	movgt	r3, #0
    849a:	2301      	movle	r3, #1
    849c:	45a9      	cmp	r9, r5
    849e:	bf38      	it	cc
    84a0:	f043 0301 	orrcc.w	r3, r3, #1
    84a4:	2b00      	cmp	r3, #0
    84a6:	d03b      	beq.n	8520 <_malloc_r+0x2a0>
    84a8:	f249 4324 	movw	r3, #37924	; 0x9424
    84ac:	f648 7abc 	movw	sl, #36796	; 0x8fbc
    84b0:	f2c0 0300 	movt	r3, #0
    84b4:	f2c0 0a00 	movt	sl, #0
    84b8:	4630      	mov	r0, r6
    84ba:	681a      	ldr	r2, [r3, #0]
    84bc:	f8da 3000 	ldr.w	r3, [sl]
    84c0:	eb05 0802 	add.w	r8, r5, r2
    84c4:	3301      	adds	r3, #1
    84c6:	bf17      	itett	ne
    84c8:	f508 5880 	addne.w	r8, r8, #4096	; 0x1000
    84cc:	f108 0810 	addeq.w	r8, r8, #16
    84d0:	f108 080f 	addne.w	r8, r8, #15
    84d4:	f428 687f 	bicne.w	r8, r8, #4080	; 0xff0
    84d8:	bf18      	it	ne
    84da:	f028 080f 	bicne.w	r8, r8, #15
    84de:	4641      	mov	r1, r8
    84e0:	f000 f9a0 	bl	8824 <_sbrk_r>
    84e4:	1c41      	adds	r1, r0, #1
    84e6:	4602      	mov	r2, r0
    84e8:	d006      	beq.n	84f8 <_malloc_r+0x278>
    84ea:	eb04 0009 	add.w	r0, r4, r9
    84ee:	42bc      	cmp	r4, r7
    84f0:	bf18      	it	ne
    84f2:	4290      	cmpne	r0, r2
    84f4:	f240 80b9 	bls.w	866a <_malloc_r+0x3ea>
    84f8:	68bc      	ldr	r4, [r7, #8]
    84fa:	6863      	ldr	r3, [r4, #4]
    84fc:	f023 0303 	bic.w	r3, r3, #3
    8500:	429d      	cmp	r5, r3
    8502:	eba3 0205 	sub.w	r2, r3, r5
    8506:	bf94      	ite	ls
    8508:	2300      	movls	r3, #0
    850a:	2301      	movhi	r3, #1
    850c:	2a0f      	cmp	r2, #15
    850e:	bfd8      	it	le
    8510:	f043 0301 	orrle.w	r3, r3, #1
    8514:	b123      	cbz	r3, 8520 <_malloc_r+0x2a0>
    8516:	4630      	mov	r0, r6
    8518:	2400      	movs	r4, #0
    851a:	f000 f97d 	bl	8818 <__malloc_unlock>
    851e:	e782      	b.n	8426 <_malloc_r+0x1a6>
    8520:	1963      	adds	r3, r4, r5
    8522:	f042 0201 	orr.w	r2, r2, #1
    8526:	4630      	mov	r0, r6
    8528:	f045 0501 	orr.w	r5, r5, #1
    852c:	6065      	str	r5, [r4, #4]
    852e:	3408      	adds	r4, #8
    8530:	60bb      	str	r3, [r7, #8]
    8532:	605a      	str	r2, [r3, #4]
    8534:	f000 f970 	bl	8818 <__malloc_unlock>
    8538:	4620      	mov	r0, r4
    853a:	b003      	add	sp, #12
    853c:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    8540:	2b14      	cmp	r3, #20
    8542:	d963      	bls.n	860c <_malloc_r+0x38c>
    8544:	2b54      	cmp	r3, #84	; 0x54
    8546:	f200 8102 	bhi.w	874e <_malloc_r+0x4ce>
    854a:	0b2b      	lsrs	r3, r5, #12
    854c:	f103 046f 	add.w	r4, r3, #111	; 0x6f
    8550:	f103 0e6e 	add.w	lr, r3, #110	; 0x6e
    8554:	00e3      	lsls	r3, r4, #3
    8556:	e6b8      	b.n	82ca <_malloc_r+0x4a>
    8558:	0a59      	lsrs	r1, r3, #9
    855a:	2904      	cmp	r1, #4
    855c:	d95c      	bls.n	8618 <_malloc_r+0x398>
    855e:	2914      	cmp	r1, #20
    8560:	f200 8113 	bhi.w	878a <_malloc_r+0x50a>
    8564:	f101 025c 	add.w	r2, r1, #92	; 0x5c
    8568:	315b      	adds	r1, #91	; 0x5b
    856a:	00d2      	lsls	r2, r2, #3
    856c:	18b8      	adds	r0, r7, r2
    856e:	58ba      	ldr	r2, [r7, r2]
    8570:	3808      	subs	r0, #8
    8572:	4290      	cmp	r0, r2
    8574:	f000 80f5 	beq.w	8762 <_malloc_r+0x4e2>
    8578:	6851      	ldr	r1, [r2, #4]
    857a:	f021 0103 	bic.w	r1, r1, #3
    857e:	428b      	cmp	r3, r1
    8580:	f080 80e3 	bcs.w	874a <_malloc_r+0x4ca>
    8584:	6892      	ldr	r2, [r2, #8]
    8586:	4290      	cmp	r0, r2
    8588:	d1f6      	bne.n	8578 <_malloc_r+0x2f8>
    858a:	68c2      	ldr	r2, [r0, #12]
    858c:	687b      	ldr	r3, [r7, #4]
    858e:	f8cc 200c 	str.w	r2, [ip, #12]
    8592:	f8cc 0008 	str.w	r0, [ip, #8]
    8596:	f8c2 c008 	str.w	ip, [r2, #8]
    859a:	f8c0 c00c 	str.w	ip, [r0, #12]
    859e:	e6dc      	b.n	835a <_malloc_r+0xda>
    85a0:	eb0c 0105 	add.w	r1, ip, r5
    85a4:	4630      	mov	r0, r6
    85a6:	f045 0501 	orr.w	r5, r5, #1
    85aa:	f8cc 5004 	str.w	r5, [ip, #4]
    85ae:	6179      	str	r1, [r7, #20]
    85b0:	f042 0501 	orr.w	r5, r2, #1
    85b4:	6139      	str	r1, [r7, #16]
    85b6:	f10c 0408 	add.w	r4, ip, #8
    85ba:	f8c1 e00c 	str.w	lr, [r1, #12]
    85be:	f8c1 e008 	str.w	lr, [r1, #8]
    85c2:	604d      	str	r5, [r1, #4]
    85c4:	f84c 2003 	str.w	r2, [ip, r3]
    85c8:	f000 f926 	bl	8818 <__malloc_unlock>
    85cc:	e72b      	b.n	8426 <_malloc_r+0x1a6>
    85ce:	f108 0801 	add.w	r8, r8, #1
    85d2:	f10c 0c08 	add.w	ip, ip, #8
    85d6:	f018 0f03 	tst.w	r8, #3
    85da:	f47f aed0 	bne.w	837e <_malloc_r+0xfe>
    85de:	e026      	b.n	862e <_malloc_r+0x3ae>
    85e0:	68d3      	ldr	r3, [r2, #12]
    85e2:	429a      	cmp	r2, r3
    85e4:	bf08      	it	eq
    85e6:	3402      	addeq	r4, #2
    85e8:	f43f ae87 	beq.w	82fa <_malloc_r+0x7a>
    85ec:	e70a      	b.n	8404 <_malloc_r+0x184>
    85ee:	4419      	add	r1, r3
    85f0:	461c      	mov	r4, r3
    85f2:	68da      	ldr	r2, [r3, #12]
    85f4:	4630      	mov	r0, r6
    85f6:	f854 5f08 	ldr.w	r5, [r4, #8]!
    85fa:	684b      	ldr	r3, [r1, #4]
    85fc:	f043 0301 	orr.w	r3, r3, #1
    8600:	604b      	str	r3, [r1, #4]
    8602:	60ea      	str	r2, [r5, #12]
    8604:	6095      	str	r5, [r2, #8]
    8606:	f000 f907 	bl	8818 <__malloc_unlock>
    860a:	e70c      	b.n	8426 <_malloc_r+0x1a6>
    860c:	f103 045c 	add.w	r4, r3, #92	; 0x5c
    8610:	f103 0e5b 	add.w	lr, r3, #91	; 0x5b
    8614:	00e3      	lsls	r3, r4, #3
    8616:	e658      	b.n	82ca <_malloc_r+0x4a>
    8618:	0999      	lsrs	r1, r3, #6
    861a:	f101 0239 	add.w	r2, r1, #57	; 0x39
    861e:	3138      	adds	r1, #56	; 0x38
    8620:	00d2      	lsls	r2, r2, #3
    8622:	e7a3      	b.n	856c <_malloc_r+0x2ec>
    8624:	f859 3908 	ldr.w	r3, [r9], #-8
    8628:	4599      	cmp	r9, r3
    862a:	f040 80e7 	bne.w	87fc <_malloc_r+0x57c>
    862e:	f014 0f03 	tst.w	r4, #3
    8632:	f104 34ff 	add.w	r4, r4, #4294967295
    8636:	d1f5      	bne.n	8624 <_malloc_r+0x3a4>
    8638:	687b      	ldr	r3, [r7, #4]
    863a:	ea23 0300 	bic.w	r3, r3, r0
    863e:	607b      	str	r3, [r7, #4]
    8640:	0040      	lsls	r0, r0, #1
    8642:	bf14      	ite	ne
    8644:	2201      	movne	r2, #1
    8646:	2200      	moveq	r2, #0
    8648:	4298      	cmp	r0, r3
    864a:	bf8c      	ite	hi
    864c:	2200      	movhi	r2, #0
    864e:	f002 0201 	andls.w	r2, r2, #1
    8652:	2a00      	cmp	r2, #0
    8654:	f43f af18 	beq.w	8488 <_malloc_r+0x208>
    8658:	4218      	tst	r0, r3
    865a:	4644      	mov	r4, r8
    865c:	f47f ae8b 	bne.w	8376 <_malloc_r+0xf6>
    8660:	0040      	lsls	r0, r0, #1
    8662:	3404      	adds	r4, #4
    8664:	4218      	tst	r0, r3
    8666:	d0fb      	beq.n	8660 <_malloc_r+0x3e0>
    8668:	e685      	b.n	8376 <_malloc_r+0xf6>
    866a:	f249 3bf4 	movw	fp, #37876	; 0x93f4
    866e:	f2c0 0b00 	movt	fp, #0
    8672:	4290      	cmp	r0, r2
    8674:	f8db 1000 	ldr.w	r1, [fp]
    8678:	4441      	add	r1, r8
    867a:	f8cb 1000 	str.w	r1, [fp]
    867e:	f000 8092 	beq.w	87a6 <_malloc_r+0x526>
    8682:	f8da 3000 	ldr.w	r3, [sl]
    8686:	3301      	adds	r3, #1
    8688:	bf0f      	iteee	eq
    868a:	f8ca 2000 	streq.w	r2, [sl]
    868e:	1a10      	subne	r0, r2, r0
    8690:	1809      	addne	r1, r1, r0
    8692:	f8cb 1000 	strne.w	r1, [fp]
    8696:	f012 0107 	ands.w	r1, r2, #7
    869a:	4630      	mov	r0, r6
    869c:	bf1f      	itttt	ne
    869e:	f1c1 0308 	rsbne	r3, r1, #8
    86a2:	f5c1 5180 	rsbne	r1, r1, #4096	; 0x1000
    86a6:	18d2      	addne	r2, r2, r3
    86a8:	3108      	addne	r1, #8
    86aa:	eb02 0308 	add.w	r3, r2, r8
    86ae:	bf08      	it	eq
    86b0:	f44f 5180 	moveq.w	r1, #4096	; 0x1000
    86b4:	f3c3 030b 	ubfx	r3, r3, #0, #12
    86b8:	9201      	str	r2, [sp, #4]
    86ba:	eba1 0803 	sub.w	r8, r1, r3
    86be:	4641      	mov	r1, r8
    86c0:	f000 f8b0 	bl	8824 <_sbrk_r>
    86c4:	9a01      	ldr	r2, [sp, #4]
    86c6:	f8db 1000 	ldr.w	r1, [fp]
    86ca:	60ba      	str	r2, [r7, #8]
    86cc:	1c43      	adds	r3, r0, #1
    86ce:	bf1b      	ittet	ne
    86d0:	1a83      	subne	r3, r0, r2
    86d2:	4443      	addne	r3, r8
    86d4:	2301      	moveq	r3, #1
    86d6:	f043 0301 	orrne.w	r3, r3, #1
    86da:	bf08      	it	eq
    86dc:	f04f 0800 	moveq.w	r8, #0
    86e0:	42bc      	cmp	r4, r7
    86e2:	4441      	add	r1, r8
    86e4:	6053      	str	r3, [r2, #4]
    86e6:	f8cb 1000 	str.w	r1, [fp]
    86ea:	d019      	beq.n	8720 <_malloc_r+0x4a0>
    86ec:	f1b9 0f0f 	cmp.w	r9, #15
    86f0:	bf9c      	itt	ls
    86f2:	2301      	movls	r3, #1
    86f4:	6053      	strls	r3, [r2, #4]
    86f6:	f67f af0e 	bls.w	8516 <_malloc_r+0x296>
    86fa:	f1a9 030c 	sub.w	r3, r9, #12
    86fe:	6862      	ldr	r2, [r4, #4]
    8700:	f023 0307 	bic.w	r3, r3, #7
    8704:	f04f 0e05 	mov.w	lr, #5
    8708:	18e0      	adds	r0, r4, r3
    870a:	2b0f      	cmp	r3, #15
    870c:	f002 0201 	and.w	r2, r2, #1
    8710:	ea42 0203 	orr.w	r2, r2, r3
    8714:	6062      	str	r2, [r4, #4]
    8716:	f8c0 e004 	str.w	lr, [r0, #4]
    871a:	f8c0 e008 	str.w	lr, [r0, #8]
    871e:	d84e      	bhi.n	87be <_malloc_r+0x53e>
    8720:	f249 431c 	movw	r3, #37916	; 0x941c
    8724:	f2c0 0300 	movt	r3, #0
    8728:	68bc      	ldr	r4, [r7, #8]
    872a:	681a      	ldr	r2, [r3, #0]
    872c:	4291      	cmp	r1, r2
    872e:	bf88      	it	hi
    8730:	6019      	strhi	r1, [r3, #0]
    8732:	f249 4320 	movw	r3, #37920	; 0x9420
    8736:	f2c0 0300 	movt	r3, #0
    873a:	681a      	ldr	r2, [r3, #0]
    873c:	4291      	cmp	r1, r2
    873e:	bf88      	it	hi
    8740:	6019      	strhi	r1, [r3, #0]
    8742:	6863      	ldr	r3, [r4, #4]
    8744:	f023 0303 	bic.w	r3, r3, #3
    8748:	e6da      	b.n	8500 <_malloc_r+0x280>
    874a:	4610      	mov	r0, r2
    874c:	e71d      	b.n	858a <_malloc_r+0x30a>
    874e:	f5b3 7faa 	cmp.w	r3, #340	; 0x154
    8752:	d80f      	bhi.n	8774 <_malloc_r+0x4f4>
    8754:	0beb      	lsrs	r3, r5, #15
    8756:	f103 0478 	add.w	r4, r3, #120	; 0x78
    875a:	f103 0e77 	add.w	lr, r3, #119	; 0x77
    875e:	00e3      	lsls	r3, r4, #3
    8760:	e5b3      	b.n	82ca <_malloc_r+0x4a>
    8762:	2201      	movs	r2, #1
    8764:	687b      	ldr	r3, [r7, #4]
    8766:	1089      	asrs	r1, r1, #2
    8768:	fa02 f101 	lsl.w	r1, r2, r1
    876c:	4602      	mov	r2, r0
    876e:	430b      	orrs	r3, r1
    8770:	607b      	str	r3, [r7, #4]
    8772:	e70c      	b.n	858e <_malloc_r+0x30e>
    8774:	f240 5254 	movw	r2, #1364	; 0x554
    8778:	4293      	cmp	r3, r2
    877a:	d80e      	bhi.n	879a <_malloc_r+0x51a>
    877c:	0cab      	lsrs	r3, r5, #18
    877e:	f103 047d 	add.w	r4, r3, #125	; 0x7d
    8782:	f103 0e7c 	add.w	lr, r3, #124	; 0x7c
    8786:	00e3      	lsls	r3, r4, #3
    8788:	e59f      	b.n	82ca <_malloc_r+0x4a>
    878a:	2954      	cmp	r1, #84	; 0x54
    878c:	d81f      	bhi.n	87ce <_malloc_r+0x54e>
    878e:	0b19      	lsrs	r1, r3, #12
    8790:	f101 026f 	add.w	r2, r1, #111	; 0x6f
    8794:	316e      	adds	r1, #110	; 0x6e
    8796:	00d2      	lsls	r2, r2, #3
    8798:	e6e8      	b.n	856c <_malloc_r+0x2ec>
    879a:	f44f 737e 	mov.w	r3, #1016	; 0x3f8
    879e:	247f      	movs	r4, #127	; 0x7f
    87a0:	f04f 0e7e 	mov.w	lr, #126	; 0x7e
    87a4:	e591      	b.n	82ca <_malloc_r+0x4a>
    87a6:	f3c0 030b 	ubfx	r3, r0, #0, #12
    87aa:	2b00      	cmp	r3, #0
    87ac:	f47f af69 	bne.w	8682 <_malloc_r+0x402>
    87b0:	68ba      	ldr	r2, [r7, #8]
    87b2:	eb09 0308 	add.w	r3, r9, r8
    87b6:	f043 0301 	orr.w	r3, r3, #1
    87ba:	6053      	str	r3, [r2, #4]
    87bc:	e7b0      	b.n	8720 <_malloc_r+0x4a0>
    87be:	f104 0108 	add.w	r1, r4, #8
    87c2:	4630      	mov	r0, r6
    87c4:	f000 f898 	bl	88f8 <_free_r>
    87c8:	f8db 1000 	ldr.w	r1, [fp]
    87cc:	e7a8      	b.n	8720 <_malloc_r+0x4a0>
    87ce:	f5b1 7faa 	cmp.w	r1, #340	; 0x154
    87d2:	d805      	bhi.n	87e0 <_malloc_r+0x560>
    87d4:	0bd9      	lsrs	r1, r3, #15
    87d6:	f101 0278 	add.w	r2, r1, #120	; 0x78
    87da:	3177      	adds	r1, #119	; 0x77
    87dc:	00d2      	lsls	r2, r2, #3
    87de:	e6c5      	b.n	856c <_malloc_r+0x2ec>
    87e0:	f240 5254 	movw	r2, #1364	; 0x554
    87e4:	4291      	cmp	r1, r2
    87e6:	bf9b      	ittet	ls
    87e8:	0c99      	lsrls	r1, r3, #18
    87ea:	f101 027d 	addls.w	r2, r1, #125	; 0x7d
    87ee:	f44f 727e 	movhi.w	r2, #1016	; 0x3f8
    87f2:	317c      	addls	r1, #124	; 0x7c
    87f4:	bf8c      	ite	hi
    87f6:	217e      	movhi	r1, #126	; 0x7e
    87f8:	00d2      	lslls	r2, r2, #3
    87fa:	e6b7      	b.n	856c <_malloc_r+0x2ec>
    87fc:	687b      	ldr	r3, [r7, #4]
    87fe:	e71f      	b.n	8640 <_malloc_r+0x3c0>
    8800:	08ec      	lsrs	r4, r5, #3
    8802:	f105 0208 	add.w	r2, r5, #8
    8806:	e5f2      	b.n	83ee <_malloc_r+0x16e>
    8808:	00008bbc 			; <UNDEFINED> instruction: 0x00008bbc

0000880c <__malloc_lock>:
    880c:	f249 4038 	movw	r0, #37944	; 0x9438
    8810:	f2c0 0000 	movt	r0, #0
    8814:	f000 b96a 	b.w	8aec <__retarget_lock_acquire_recursive>

00008818 <__malloc_unlock>:
    8818:	f249 4038 	movw	r0, #37944	; 0x9438
    881c:	f2c0 0000 	movt	r0, #0
    8820:	f000 b96c 	b.w	8afc <__retarget_lock_release_recursive>

00008824 <_sbrk_r>:
    8824:	b538      	push	{r3, r4, r5, lr}
    8826:	f249 444c 	movw	r4, #37964	; 0x944c
    882a:	f2c0 0400 	movt	r4, #0
    882e:	4605      	mov	r5, r0
    8830:	4608      	mov	r0, r1
    8832:	2300      	movs	r3, #0
    8834:	6023      	str	r3, [r4, #0]
    8836:	f7ff eca0 	blx	8178 <_sbrk>
    883a:	1c43      	adds	r3, r0, #1
    883c:	d000      	beq.n	8840 <_sbrk_r+0x1c>
    883e:	bd38      	pop	{r3, r4, r5, pc}
    8840:	6823      	ldr	r3, [r4, #0]
    8842:	2b00      	cmp	r3, #0
    8844:	d0fb      	beq.n	883e <_sbrk_r+0x1a>
    8846:	602b      	str	r3, [r5, #0]
    8848:	bd38      	pop	{r3, r4, r5, pc}
    884a:	bf00      	nop

0000884c <_malloc_trim_r>:
    884c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    884e:	f648 37b4 	movw	r7, #35764	; 0x8bb4
    8852:	f2c0 0700 	movt	r7, #0
    8856:	460c      	mov	r4, r1
    8858:	4606      	mov	r6, r0
    885a:	f7ff ffd7 	bl	880c <__malloc_lock>
    885e:	68bb      	ldr	r3, [r7, #8]
    8860:	f5c4 617e 	rsb	r1, r4, #4064	; 0xfe0
    8864:	310f      	adds	r1, #15
    8866:	685d      	ldr	r5, [r3, #4]
    8868:	f025 0503 	bic.w	r5, r5, #3
    886c:	4429      	add	r1, r5
    886e:	f421 617f 	bic.w	r1, r1, #4080	; 0xff0
    8872:	f021 010f 	bic.w	r1, r1, #15
    8876:	f5a1 5480 	sub.w	r4, r1, #4096	; 0x1000
    887a:	f5b4 5f80 	cmp.w	r4, #4096	; 0x1000
    887e:	db07      	blt.n	8890 <_malloc_trim_r+0x44>
    8880:	2100      	movs	r1, #0
    8882:	4630      	mov	r0, r6
    8884:	f7ff ffce 	bl	8824 <_sbrk_r>
    8888:	68bb      	ldr	r3, [r7, #8]
    888a:	442b      	add	r3, r5
    888c:	4298      	cmp	r0, r3
    888e:	d004      	beq.n	889a <_malloc_trim_r+0x4e>
    8890:	4630      	mov	r0, r6
    8892:	f7ff ffc1 	bl	8818 <__malloc_unlock>
    8896:	2000      	movs	r0, #0
    8898:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
    889a:	4261      	negs	r1, r4
    889c:	4630      	mov	r0, r6
    889e:	f7ff ffc1 	bl	8824 <_sbrk_r>
    88a2:	3001      	adds	r0, #1
    88a4:	d010      	beq.n	88c8 <_malloc_trim_r+0x7c>
    88a6:	68ba      	ldr	r2, [r7, #8]
    88a8:	f249 33f4 	movw	r3, #37876	; 0x93f4
    88ac:	f2c0 0300 	movt	r3, #0
    88b0:	1b2d      	subs	r5, r5, r4
    88b2:	4630      	mov	r0, r6
    88b4:	f045 0501 	orr.w	r5, r5, #1
    88b8:	6819      	ldr	r1, [r3, #0]
    88ba:	6055      	str	r5, [r2, #4]
    88bc:	1b09      	subs	r1, r1, r4
    88be:	6019      	str	r1, [r3, #0]
    88c0:	f7ff ffaa 	bl	8818 <__malloc_unlock>
    88c4:	2001      	movs	r0, #1
    88c6:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
    88c8:	2100      	movs	r1, #0
    88ca:	4630      	mov	r0, r6
    88cc:	f7ff ffaa 	bl	8824 <_sbrk_r>
    88d0:	68ba      	ldr	r2, [r7, #8]
    88d2:	1a83      	subs	r3, r0, r2
    88d4:	2b0f      	cmp	r3, #15
    88d6:	dddb      	ble.n	8890 <_malloc_trim_r+0x44>
    88d8:	f648 74bc 	movw	r4, #36796	; 0x8fbc
    88dc:	f2c0 0400 	movt	r4, #0
    88e0:	f249 31f4 	movw	r1, #37876	; 0x93f4
    88e4:	f2c0 0100 	movt	r1, #0
    88e8:	6824      	ldr	r4, [r4, #0]
    88ea:	f043 0301 	orr.w	r3, r3, #1
    88ee:	6053      	str	r3, [r2, #4]
    88f0:	1b00      	subs	r0, r0, r4
    88f2:	6008      	str	r0, [r1, #0]
    88f4:	e7cc      	b.n	8890 <_malloc_trim_r+0x44>
    88f6:	bf00      	nop

000088f8 <_free_r>:
    88f8:	2900      	cmp	r1, #0
    88fa:	d049      	beq.n	8990 <_free_r+0x98>
    88fc:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
    8900:	460d      	mov	r5, r1
    8902:	4680      	mov	r8, r0
    8904:	f7ff ff82 	bl	880c <__malloc_lock>
    8908:	f855 7c04 	ldr.w	r7, [r5, #-4]
    890c:	f648 31b4 	movw	r1, #35764	; 0x8bb4
    8910:	f2c0 0100 	movt	r1, #0
    8914:	f1a5 0408 	sub.w	r4, r5, #8
    8918:	f027 0301 	bic.w	r3, r7, #1
    891c:	18e2      	adds	r2, r4, r3
    891e:	688e      	ldr	r6, [r1, #8]
    8920:	6850      	ldr	r0, [r2, #4]
    8922:	42b2      	cmp	r2, r6
    8924:	f020 0003 	bic.w	r0, r0, #3
    8928:	d063      	beq.n	89f2 <_free_r+0xfa>
    892a:	07fe      	lsls	r6, r7, #31
    892c:	6050      	str	r0, [r2, #4]
    892e:	d40b      	bmi.n	8948 <_free_r+0x50>
    8930:	f855 5c08 	ldr.w	r5, [r5, #-8]
    8934:	f101 0708 	add.w	r7, r1, #8
    8938:	1b64      	subs	r4, r4, r5
    893a:	442b      	add	r3, r5
    893c:	68a5      	ldr	r5, [r4, #8]
    893e:	42bd      	cmp	r5, r7
    8940:	d078      	beq.n	8a34 <_free_r+0x13c>
    8942:	68e7      	ldr	r7, [r4, #12]
    8944:	60ef      	str	r7, [r5, #12]
    8946:	60bd      	str	r5, [r7, #8]
    8948:	1815      	adds	r5, r2, r0
    894a:	686d      	ldr	r5, [r5, #4]
    894c:	07ed      	lsls	r5, r5, #31
    894e:	bf42      	ittt	mi
    8950:	f043 0201 	orrmi.w	r2, r3, #1
    8954:	6062      	strmi	r2, [r4, #4]
    8956:	50e3      	strmi	r3, [r4, r3]
    8958:	d53b      	bpl.n	89d2 <_free_r+0xda>
    895a:	f5b3 7f00 	cmp.w	r3, #512	; 0x200
    895e:	d218      	bcs.n	8992 <_free_r+0x9a>
    8960:	08db      	lsrs	r3, r3, #3
    8962:	2201      	movs	r2, #1
    8964:	189d      	adds	r5, r3, r2
    8966:	6848      	ldr	r0, [r1, #4]
    8968:	109b      	asrs	r3, r3, #2
    896a:	f851 7035 	ldr.w	r7, [r1, r5, lsl #3]
    896e:	fa02 f303 	lsl.w	r3, r2, r3
    8972:	eb01 02c5 	add.w	r2, r1, r5, lsl #3
    8976:	4303      	orrs	r3, r0
    8978:	3a08      	subs	r2, #8
    897a:	604b      	str	r3, [r1, #4]
    897c:	60e2      	str	r2, [r4, #12]
    897e:	60a7      	str	r7, [r4, #8]
    8980:	f841 4035 	str.w	r4, [r1, r5, lsl #3]
    8984:	60fc      	str	r4, [r7, #12]
    8986:	4640      	mov	r0, r8
    8988:	e8bd 41f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, lr}
    898c:	f7ff bf44 	b.w	8818 <__malloc_unlock>
    8990:	4770      	bx	lr
    8992:	0a5a      	lsrs	r2, r3, #9
    8994:	2a04      	cmp	r2, #4
    8996:	d85b      	bhi.n	8a50 <_free_r+0x158>
    8998:	099a      	lsrs	r2, r3, #6
    899a:	f102 0039 	add.w	r0, r2, #57	; 0x39
    899e:	f102 0538 	add.w	r5, r2, #56	; 0x38
    89a2:	00c2      	lsls	r2, r0, #3
    89a4:	1888      	adds	r0, r1, r2
    89a6:	588a      	ldr	r2, [r1, r2]
    89a8:	3808      	subs	r0, #8
    89aa:	4290      	cmp	r0, r2
    89ac:	d058      	beq.n	8a60 <_free_r+0x168>
    89ae:	6851      	ldr	r1, [r2, #4]
    89b0:	f021 0103 	bic.w	r1, r1, #3
    89b4:	428b      	cmp	r3, r1
    89b6:	d23b      	bcs.n	8a30 <_free_r+0x138>
    89b8:	6892      	ldr	r2, [r2, #8]
    89ba:	4290      	cmp	r0, r2
    89bc:	d1f7      	bne.n	89ae <_free_r+0xb6>
    89be:	68c3      	ldr	r3, [r0, #12]
    89c0:	60a0      	str	r0, [r4, #8]
    89c2:	60e3      	str	r3, [r4, #12]
    89c4:	609c      	str	r4, [r3, #8]
    89c6:	60c4      	str	r4, [r0, #12]
    89c8:	4640      	mov	r0, r8
    89ca:	e8bd 41f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, lr}
    89ce:	f7ff bf23 	b.w	8818 <__malloc_unlock>
    89d2:	6895      	ldr	r5, [r2, #8]
    89d4:	4403      	add	r3, r0
    89d6:	483f      	ldr	r0, [pc, #252]	; (8ad4 <_free_r+0x1dc>)
    89d8:	4285      	cmp	r5, r0
    89da:	d04a      	beq.n	8a72 <_free_r+0x17a>
    89dc:	68d0      	ldr	r0, [r2, #12]
    89de:	f5b3 7f00 	cmp.w	r3, #512	; 0x200
    89e2:	f043 0201 	orr.w	r2, r3, #1
    89e6:	60e8      	str	r0, [r5, #12]
    89e8:	6085      	str	r5, [r0, #8]
    89ea:	6062      	str	r2, [r4, #4]
    89ec:	50e3      	str	r3, [r4, r3]
    89ee:	d2d0      	bcs.n	8992 <_free_r+0x9a>
    89f0:	e7b6      	b.n	8960 <_free_r+0x68>
    89f2:	07ff      	lsls	r7, r7, #31
    89f4:	4403      	add	r3, r0
    89f6:	d407      	bmi.n	8a08 <_free_r+0x110>
    89f8:	f855 2c08 	ldr.w	r2, [r5, #-8]
    89fc:	1aa4      	subs	r4, r4, r2
    89fe:	4413      	add	r3, r2
    8a00:	68a0      	ldr	r0, [r4, #8]
    8a02:	68e2      	ldr	r2, [r4, #12]
    8a04:	60c2      	str	r2, [r0, #12]
    8a06:	6090      	str	r0, [r2, #8]
    8a08:	f648 72c0 	movw	r2, #36800	; 0x8fc0
    8a0c:	f2c0 0200 	movt	r2, #0
    8a10:	f043 0001 	orr.w	r0, r3, #1
    8a14:	6060      	str	r0, [r4, #4]
    8a16:	6812      	ldr	r2, [r2, #0]
    8a18:	608c      	str	r4, [r1, #8]
    8a1a:	4293      	cmp	r3, r2
    8a1c:	d3b3      	bcc.n	8986 <_free_r+0x8e>
    8a1e:	f249 4324 	movw	r3, #37924	; 0x9424
    8a22:	f2c0 0300 	movt	r3, #0
    8a26:	4640      	mov	r0, r8
    8a28:	6819      	ldr	r1, [r3, #0]
    8a2a:	f7ff ff0f 	bl	884c <_malloc_trim_r>
    8a2e:	e7aa      	b.n	8986 <_free_r+0x8e>
    8a30:	4610      	mov	r0, r2
    8a32:	e7c4      	b.n	89be <_free_r+0xc6>
    8a34:	1811      	adds	r1, r2, r0
    8a36:	6849      	ldr	r1, [r1, #4]
    8a38:	07c9      	lsls	r1, r1, #31
    8a3a:	d445      	bmi.n	8ac8 <_free_r+0x1d0>
    8a3c:	6891      	ldr	r1, [r2, #8]
    8a3e:	4403      	add	r3, r0
    8a40:	68d2      	ldr	r2, [r2, #12]
    8a42:	f043 0001 	orr.w	r0, r3, #1
    8a46:	60ca      	str	r2, [r1, #12]
    8a48:	6091      	str	r1, [r2, #8]
    8a4a:	6060      	str	r0, [r4, #4]
    8a4c:	50e3      	str	r3, [r4, r3]
    8a4e:	e79a      	b.n	8986 <_free_r+0x8e>
    8a50:	2a14      	cmp	r2, #20
    8a52:	d817      	bhi.n	8a84 <_free_r+0x18c>
    8a54:	f102 005c 	add.w	r0, r2, #92	; 0x5c
    8a58:	f102 055b 	add.w	r5, r2, #91	; 0x5b
    8a5c:	00c2      	lsls	r2, r0, #3
    8a5e:	e7a1      	b.n	89a4 <_free_r+0xac>
    8a60:	10aa      	asrs	r2, r5, #2
    8a62:	2301      	movs	r3, #1
    8a64:	684d      	ldr	r5, [r1, #4]
    8a66:	fa03 f202 	lsl.w	r2, r3, r2
    8a6a:	4603      	mov	r3, r0
    8a6c:	432a      	orrs	r2, r5
    8a6e:	604a      	str	r2, [r1, #4]
    8a70:	e7a6      	b.n	89c0 <_free_r+0xc8>
    8a72:	614c      	str	r4, [r1, #20]
    8a74:	f043 0201 	orr.w	r2, r3, #1
    8a78:	610c      	str	r4, [r1, #16]
    8a7a:	60e5      	str	r5, [r4, #12]
    8a7c:	60a5      	str	r5, [r4, #8]
    8a7e:	6062      	str	r2, [r4, #4]
    8a80:	50e3      	str	r3, [r4, r3]
    8a82:	e780      	b.n	8986 <_free_r+0x8e>
    8a84:	2a54      	cmp	r2, #84	; 0x54
    8a86:	d806      	bhi.n	8a96 <_free_r+0x19e>
    8a88:	0b1a      	lsrs	r2, r3, #12
    8a8a:	f102 006f 	add.w	r0, r2, #111	; 0x6f
    8a8e:	f102 056e 	add.w	r5, r2, #110	; 0x6e
    8a92:	00c2      	lsls	r2, r0, #3
    8a94:	e786      	b.n	89a4 <_free_r+0xac>
    8a96:	f5b2 7faa 	cmp.w	r2, #340	; 0x154
    8a9a:	d806      	bhi.n	8aaa <_free_r+0x1b2>
    8a9c:	0bda      	lsrs	r2, r3, #15
    8a9e:	f102 0078 	add.w	r0, r2, #120	; 0x78
    8aa2:	f102 0577 	add.w	r5, r2, #119	; 0x77
    8aa6:	00c2      	lsls	r2, r0, #3
    8aa8:	e77c      	b.n	89a4 <_free_r+0xac>
    8aaa:	f240 5054 	movw	r0, #1364	; 0x554
    8aae:	4282      	cmp	r2, r0
    8ab0:	bf9d      	ittte	ls
    8ab2:	0c9a      	lsrls	r2, r3, #18
    8ab4:	f102 007d 	addls.w	r0, r2, #125	; 0x7d
    8ab8:	f102 057c 	addls.w	r5, r2, #124	; 0x7c
    8abc:	f44f 727e 	movhi.w	r2, #1016	; 0x3f8
    8ac0:	bf8c      	ite	hi
    8ac2:	257e      	movhi	r5, #126	; 0x7e
    8ac4:	00c2      	lslls	r2, r0, #3
    8ac6:	e76d      	b.n	89a4 <_free_r+0xac>
    8ac8:	f043 0101 	orr.w	r1, r3, #1
    8acc:	6061      	str	r1, [r4, #4]
    8ace:	6013      	str	r3, [r2, #0]
    8ad0:	e759      	b.n	8986 <_free_r+0x8e>
    8ad2:	bf00      	nop
    8ad4:	00008bbc 			; <UNDEFINED> instruction: 0x00008bbc

00008ad8 <__retarget_lock_init>:
    8ad8:	4770      	bx	lr
    8ada:	bf00      	nop

00008adc <__retarget_lock_init_recursive>:
    8adc:	4770      	bx	lr
    8ade:	bf00      	nop

00008ae0 <__retarget_lock_close>:
    8ae0:	4770      	bx	lr
    8ae2:	bf00      	nop

00008ae4 <__retarget_lock_close_recursive>:
    8ae4:	4770      	bx	lr
    8ae6:	bf00      	nop

00008ae8 <__retarget_lock_acquire>:
    8ae8:	4770      	bx	lr
    8aea:	bf00      	nop

00008aec <__retarget_lock_acquire_recursive>:
    8aec:	4770      	bx	lr
    8aee:	bf00      	nop

00008af0 <__retarget_lock_try_acquire>:
    8af0:	2001      	movs	r0, #1
    8af2:	4770      	bx	lr

00008af4 <__retarget_lock_try_acquire_recursive>:
    8af4:	2001      	movs	r0, #1
    8af6:	4770      	bx	lr

00008af8 <__retarget_lock_release>:
    8af8:	4770      	bx	lr
    8afa:	bf00      	nop

00008afc <__retarget_lock_release_recursive>:
    8afc:	4770      	bx	lr
    8afe:	bf00      	nop

00008b00 <cleanup_glue>:
    8b00:	b538      	push	{r3, r4, r5, lr}
    8b02:	460c      	mov	r4, r1
    8b04:	6809      	ldr	r1, [r1, #0]
    8b06:	4605      	mov	r5, r0
    8b08:	b109      	cbz	r1, 8b0e <cleanup_glue+0xe>
    8b0a:	f7ff fff9 	bl	8b00 <cleanup_glue>
    8b0e:	4621      	mov	r1, r4
    8b10:	4628      	mov	r0, r5
    8b12:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
    8b16:	f7ff beef 	b.w	88f8 <_free_r>
    8b1a:	bf00      	nop

00008b1c <_reclaim_reent>:
    8b1c:	f648 73c4 	movw	r3, #36804	; 0x8fc4
    8b20:	f2c0 0300 	movt	r3, #0
    8b24:	681b      	ldr	r3, [r3, #0]
    8b26:	4283      	cmp	r3, r0
    8b28:	d03c      	beq.n	8ba4 <_reclaim_reent+0x88>
    8b2a:	6cc3      	ldr	r3, [r0, #76]	; 0x4c
    8b2c:	b570      	push	{r4, r5, r6, lr}
    8b2e:	4605      	mov	r5, r0
    8b30:	b18b      	cbz	r3, 8b56 <_reclaim_reent+0x3a>
    8b32:	2600      	movs	r6, #0
    8b34:	5999      	ldr	r1, [r3, r6]
    8b36:	b139      	cbz	r1, 8b48 <_reclaim_reent+0x2c>
    8b38:	680c      	ldr	r4, [r1, #0]
    8b3a:	4628      	mov	r0, r5
    8b3c:	f7ff fedc 	bl	88f8 <_free_r>
    8b40:	4621      	mov	r1, r4
    8b42:	2c00      	cmp	r4, #0
    8b44:	d1f8      	bne.n	8b38 <_reclaim_reent+0x1c>
    8b46:	6ceb      	ldr	r3, [r5, #76]	; 0x4c
    8b48:	3604      	adds	r6, #4
    8b4a:	2e80      	cmp	r6, #128	; 0x80
    8b4c:	d1f2      	bne.n	8b34 <_reclaim_reent+0x18>
    8b4e:	4619      	mov	r1, r3
    8b50:	4628      	mov	r0, r5
    8b52:	f7ff fed1 	bl	88f8 <_free_r>
    8b56:	6c29      	ldr	r1, [r5, #64]	; 0x40
    8b58:	b111      	cbz	r1, 8b60 <_reclaim_reent+0x44>
    8b5a:	4628      	mov	r0, r5
    8b5c:	f7ff fecc 	bl	88f8 <_free_r>
    8b60:	f8d5 1148 	ldr.w	r1, [r5, #328]	; 0x148
    8b64:	b151      	cbz	r1, 8b7c <_reclaim_reent+0x60>
    8b66:	f505 76a6 	add.w	r6, r5, #332	; 0x14c
    8b6a:	42b1      	cmp	r1, r6
    8b6c:	d006      	beq.n	8b7c <_reclaim_reent+0x60>
    8b6e:	680c      	ldr	r4, [r1, #0]
    8b70:	4628      	mov	r0, r5
    8b72:	f7ff fec1 	bl	88f8 <_free_r>
    8b76:	42a6      	cmp	r6, r4
    8b78:	4621      	mov	r1, r4
    8b7a:	d1f8      	bne.n	8b6e <_reclaim_reent+0x52>
    8b7c:	6d69      	ldr	r1, [r5, #84]	; 0x54
    8b7e:	b111      	cbz	r1, 8b86 <_reclaim_reent+0x6a>
    8b80:	4628      	mov	r0, r5
    8b82:	f7ff feb9 	bl	88f8 <_free_r>
    8b86:	6bab      	ldr	r3, [r5, #56]	; 0x38
    8b88:	b903      	cbnz	r3, 8b8c <_reclaim_reent+0x70>
    8b8a:	bd70      	pop	{r4, r5, r6, pc}
    8b8c:	6beb      	ldr	r3, [r5, #60]	; 0x3c
    8b8e:	4628      	mov	r0, r5
    8b90:	4798      	blx	r3
    8b92:	f8d5 12e0 	ldr.w	r1, [r5, #736]	; 0x2e0
    8b96:	2900      	cmp	r1, #0
    8b98:	d0f7      	beq.n	8b8a <_reclaim_reent+0x6e>
    8b9a:	4628      	mov	r0, r5
    8b9c:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
    8ba0:	f7ff bfae 	b.w	8b00 <cleanup_glue>
    8ba4:	4770      	bx	lr
    8ba6:	bf00      	nop

Disassembly of section .rodata:

00008ba8 <_global_impure_ptr>:
    8ba8:	00008fc8 	andeq	r8, r0, r8, asr #31

Disassembly of section .data:

00008bb0 <gpio>:
    8bb0:	3f200000 	svccc	0x00200000

00008bb4 <__malloc_av_>:
	...
    8bbc:	00008bb4 			; <UNDEFINED> instruction: 0x00008bb4
    8bc0:	00008bb4 			; <UNDEFINED> instruction: 0x00008bb4
    8bc4:	00008bbc 			; <UNDEFINED> instruction: 0x00008bbc
    8bc8:	00008bbc 			; <UNDEFINED> instruction: 0x00008bbc
    8bcc:	00008bc4 	andeq	r8, r0, r4, asr #23
    8bd0:	00008bc4 	andeq	r8, r0, r4, asr #23
    8bd4:	00008bcc 	andeq	r8, r0, ip, asr #23
    8bd8:	00008bcc 	andeq	r8, r0, ip, asr #23
    8bdc:	00008bd4 	ldrdeq	r8, [r0], -r4
    8be0:	00008bd4 	ldrdeq	r8, [r0], -r4
    8be4:	00008bdc 	ldrdeq	r8, [r0], -ip
    8be8:	00008bdc 	ldrdeq	r8, [r0], -ip
    8bec:	00008be4 	andeq	r8, r0, r4, ror #23
    8bf0:	00008be4 	andeq	r8, r0, r4, ror #23
    8bf4:	00008bec 	andeq	r8, r0, ip, ror #23
    8bf8:	00008bec 	andeq	r8, r0, ip, ror #23
    8bfc:	00008bf4 	strdeq	r8, [r0], -r4
    8c00:	00008bf4 	strdeq	r8, [r0], -r4
    8c04:	00008bfc 	strdeq	r8, [r0], -ip
    8c08:	00008bfc 	strdeq	r8, [r0], -ip
    8c0c:	00008c04 	andeq	r8, r0, r4, lsl #24
    8c10:	00008c04 	andeq	r8, r0, r4, lsl #24
    8c14:	00008c0c 	andeq	r8, r0, ip, lsl #24
    8c18:	00008c0c 	andeq	r8, r0, ip, lsl #24
    8c1c:	00008c14 	andeq	r8, r0, r4, lsl ip
    8c20:	00008c14 	andeq	r8, r0, r4, lsl ip
    8c24:	00008c1c 	andeq	r8, r0, ip, lsl ip
    8c28:	00008c1c 	andeq	r8, r0, ip, lsl ip
    8c2c:	00008c24 	andeq	r8, r0, r4, lsr #24
    8c30:	00008c24 	andeq	r8, r0, r4, lsr #24
    8c34:	00008c2c 	andeq	r8, r0, ip, lsr #24
    8c38:	00008c2c 	andeq	r8, r0, ip, lsr #24
    8c3c:	00008c34 	andeq	r8, r0, r4, lsr ip
    8c40:	00008c34 	andeq	r8, r0, r4, lsr ip
    8c44:	00008c3c 	andeq	r8, r0, ip, lsr ip
    8c48:	00008c3c 	andeq	r8, r0, ip, lsr ip
    8c4c:	00008c44 	andeq	r8, r0, r4, asr #24
    8c50:	00008c44 	andeq	r8, r0, r4, asr #24
    8c54:	00008c4c 	andeq	r8, r0, ip, asr #24
    8c58:	00008c4c 	andeq	r8, r0, ip, asr #24
    8c5c:	00008c54 	andeq	r8, r0, r4, asr ip
    8c60:	00008c54 	andeq	r8, r0, r4, asr ip
    8c64:	00008c5c 	andeq	r8, r0, ip, asr ip
    8c68:	00008c5c 	andeq	r8, r0, ip, asr ip
    8c6c:	00008c64 	andeq	r8, r0, r4, ror #24
    8c70:	00008c64 	andeq	r8, r0, r4, ror #24
    8c74:	00008c6c 	andeq	r8, r0, ip, ror #24
    8c78:	00008c6c 	andeq	r8, r0, ip, ror #24
    8c7c:	00008c74 	andeq	r8, r0, r4, ror ip
    8c80:	00008c74 	andeq	r8, r0, r4, ror ip
    8c84:	00008c7c 	andeq	r8, r0, ip, ror ip
    8c88:	00008c7c 	andeq	r8, r0, ip, ror ip
    8c8c:	00008c84 	andeq	r8, r0, r4, lsl #25
    8c90:	00008c84 	andeq	r8, r0, r4, lsl #25
    8c94:	00008c8c 	andeq	r8, r0, ip, lsl #25
    8c98:	00008c8c 	andeq	r8, r0, ip, lsl #25
    8c9c:	00008c94 	muleq	r0, r4, ip
    8ca0:	00008c94 	muleq	r0, r4, ip
    8ca4:	00008c9c 	muleq	r0, ip, ip
    8ca8:	00008c9c 	muleq	r0, ip, ip
    8cac:	00008ca4 	andeq	r8, r0, r4, lsr #25
    8cb0:	00008ca4 	andeq	r8, r0, r4, lsr #25
    8cb4:	00008cac 	andeq	r8, r0, ip, lsr #25
    8cb8:	00008cac 	andeq	r8, r0, ip, lsr #25
    8cbc:	00008cb4 			; <UNDEFINED> instruction: 0x00008cb4
    8cc0:	00008cb4 			; <UNDEFINED> instruction: 0x00008cb4
    8cc4:	00008cbc 			; <UNDEFINED> instruction: 0x00008cbc
    8cc8:	00008cbc 			; <UNDEFINED> instruction: 0x00008cbc
    8ccc:	00008cc4 	andeq	r8, r0, r4, asr #25
    8cd0:	00008cc4 	andeq	r8, r0, r4, asr #25
    8cd4:	00008ccc 	andeq	r8, r0, ip, asr #25
    8cd8:	00008ccc 	andeq	r8, r0, ip, asr #25
    8cdc:	00008cd4 	ldrdeq	r8, [r0], -r4
    8ce0:	00008cd4 	ldrdeq	r8, [r0], -r4
    8ce4:	00008cdc 	ldrdeq	r8, [r0], -ip
    8ce8:	00008cdc 	ldrdeq	r8, [r0], -ip
    8cec:	00008ce4 	andeq	r8, r0, r4, ror #25
    8cf0:	00008ce4 	andeq	r8, r0, r4, ror #25
    8cf4:	00008cec 	andeq	r8, r0, ip, ror #25
    8cf8:	00008cec 	andeq	r8, r0, ip, ror #25
    8cfc:	00008cf4 	strdeq	r8, [r0], -r4
    8d00:	00008cf4 	strdeq	r8, [r0], -r4
    8d04:	00008cfc 	strdeq	r8, [r0], -ip
    8d08:	00008cfc 	strdeq	r8, [r0], -ip
    8d0c:	00008d04 	andeq	r8, r0, r4, lsl #26
    8d10:	00008d04 	andeq	r8, r0, r4, lsl #26
    8d14:	00008d0c 	andeq	r8, r0, ip, lsl #26
    8d18:	00008d0c 	andeq	r8, r0, ip, lsl #26
    8d1c:	00008d14 	andeq	r8, r0, r4, lsl sp
    8d20:	00008d14 	andeq	r8, r0, r4, lsl sp
    8d24:	00008d1c 	andeq	r8, r0, ip, lsl sp
    8d28:	00008d1c 	andeq	r8, r0, ip, lsl sp
    8d2c:	00008d24 	andeq	r8, r0, r4, lsr #26
    8d30:	00008d24 	andeq	r8, r0, r4, lsr #26
    8d34:	00008d2c 	andeq	r8, r0, ip, lsr #26
    8d38:	00008d2c 	andeq	r8, r0, ip, lsr #26
    8d3c:	00008d34 	andeq	r8, r0, r4, lsr sp
    8d40:	00008d34 	andeq	r8, r0, r4, lsr sp
    8d44:	00008d3c 	andeq	r8, r0, ip, lsr sp
    8d48:	00008d3c 	andeq	r8, r0, ip, lsr sp
    8d4c:	00008d44 	andeq	r8, r0, r4, asr #26
    8d50:	00008d44 	andeq	r8, r0, r4, asr #26
    8d54:	00008d4c 	andeq	r8, r0, ip, asr #26
    8d58:	00008d4c 	andeq	r8, r0, ip, asr #26
    8d5c:	00008d54 	andeq	r8, r0, r4, asr sp
    8d60:	00008d54 	andeq	r8, r0, r4, asr sp
    8d64:	00008d5c 	andeq	r8, r0, ip, asr sp
    8d68:	00008d5c 	andeq	r8, r0, ip, asr sp
    8d6c:	00008d64 	andeq	r8, r0, r4, ror #26
    8d70:	00008d64 	andeq	r8, r0, r4, ror #26
    8d74:	00008d6c 	andeq	r8, r0, ip, ror #26
    8d78:	00008d6c 	andeq	r8, r0, ip, ror #26
    8d7c:	00008d74 	andeq	r8, r0, r4, ror sp
    8d80:	00008d74 	andeq	r8, r0, r4, ror sp
    8d84:	00008d7c 	andeq	r8, r0, ip, ror sp
    8d88:	00008d7c 	andeq	r8, r0, ip, ror sp
    8d8c:	00008d84 	andeq	r8, r0, r4, lsl #27
    8d90:	00008d84 	andeq	r8, r0, r4, lsl #27
    8d94:	00008d8c 	andeq	r8, r0, ip, lsl #27
    8d98:	00008d8c 	andeq	r8, r0, ip, lsl #27
    8d9c:	00008d94 	muleq	r0, r4, sp
    8da0:	00008d94 	muleq	r0, r4, sp
    8da4:	00008d9c 	muleq	r0, ip, sp
    8da8:	00008d9c 	muleq	r0, ip, sp
    8dac:	00008da4 	andeq	r8, r0, r4, lsr #27
    8db0:	00008da4 	andeq	r8, r0, r4, lsr #27
    8db4:	00008dac 	andeq	r8, r0, ip, lsr #27
    8db8:	00008dac 	andeq	r8, r0, ip, lsr #27
    8dbc:	00008db4 			; <UNDEFINED> instruction: 0x00008db4
    8dc0:	00008db4 			; <UNDEFINED> instruction: 0x00008db4
    8dc4:	00008dbc 			; <UNDEFINED> instruction: 0x00008dbc
    8dc8:	00008dbc 			; <UNDEFINED> instruction: 0x00008dbc
    8dcc:	00008dc4 	andeq	r8, r0, r4, asr #27
    8dd0:	00008dc4 	andeq	r8, r0, r4, asr #27
    8dd4:	00008dcc 	andeq	r8, r0, ip, asr #27
    8dd8:	00008dcc 	andeq	r8, r0, ip, asr #27
    8ddc:	00008dd4 	ldrdeq	r8, [r0], -r4
    8de0:	00008dd4 	ldrdeq	r8, [r0], -r4
    8de4:	00008ddc 	ldrdeq	r8, [r0], -ip
    8de8:	00008ddc 	ldrdeq	r8, [r0], -ip
    8dec:	00008de4 	andeq	r8, r0, r4, ror #27
    8df0:	00008de4 	andeq	r8, r0, r4, ror #27
    8df4:	00008dec 	andeq	r8, r0, ip, ror #27
    8df8:	00008dec 	andeq	r8, r0, ip, ror #27
    8dfc:	00008df4 	strdeq	r8, [r0], -r4
    8e00:	00008df4 	strdeq	r8, [r0], -r4
    8e04:	00008dfc 	strdeq	r8, [r0], -ip
    8e08:	00008dfc 	strdeq	r8, [r0], -ip
    8e0c:	00008e04 	andeq	r8, r0, r4, lsl #28
    8e10:	00008e04 	andeq	r8, r0, r4, lsl #28
    8e14:	00008e0c 	andeq	r8, r0, ip, lsl #28
    8e18:	00008e0c 	andeq	r8, r0, ip, lsl #28
    8e1c:	00008e14 	andeq	r8, r0, r4, lsl lr
    8e20:	00008e14 	andeq	r8, r0, r4, lsl lr
    8e24:	00008e1c 	andeq	r8, r0, ip, lsl lr
    8e28:	00008e1c 	andeq	r8, r0, ip, lsl lr
    8e2c:	00008e24 	andeq	r8, r0, r4, lsr #28
    8e30:	00008e24 	andeq	r8, r0, r4, lsr #28
    8e34:	00008e2c 	andeq	r8, r0, ip, lsr #28
    8e38:	00008e2c 	andeq	r8, r0, ip, lsr #28
    8e3c:	00008e34 	andeq	r8, r0, r4, lsr lr
    8e40:	00008e34 	andeq	r8, r0, r4, lsr lr
    8e44:	00008e3c 	andeq	r8, r0, ip, lsr lr
    8e48:	00008e3c 	andeq	r8, r0, ip, lsr lr
    8e4c:	00008e44 	andeq	r8, r0, r4, asr #28
    8e50:	00008e44 	andeq	r8, r0, r4, asr #28
    8e54:	00008e4c 	andeq	r8, r0, ip, asr #28
    8e58:	00008e4c 	andeq	r8, r0, ip, asr #28
    8e5c:	00008e54 	andeq	r8, r0, r4, asr lr
    8e60:	00008e54 	andeq	r8, r0, r4, asr lr
    8e64:	00008e5c 	andeq	r8, r0, ip, asr lr
    8e68:	00008e5c 	andeq	r8, r0, ip, asr lr
    8e6c:	00008e64 	andeq	r8, r0, r4, ror #28
    8e70:	00008e64 	andeq	r8, r0, r4, ror #28
    8e74:	00008e6c 	andeq	r8, r0, ip, ror #28
    8e78:	00008e6c 	andeq	r8, r0, ip, ror #28
    8e7c:	00008e74 	andeq	r8, r0, r4, ror lr
    8e80:	00008e74 	andeq	r8, r0, r4, ror lr
    8e84:	00008e7c 	andeq	r8, r0, ip, ror lr
    8e88:	00008e7c 	andeq	r8, r0, ip, ror lr
    8e8c:	00008e84 	andeq	r8, r0, r4, lsl #29
    8e90:	00008e84 	andeq	r8, r0, r4, lsl #29
    8e94:	00008e8c 	andeq	r8, r0, ip, lsl #29
    8e98:	00008e8c 	andeq	r8, r0, ip, lsl #29
    8e9c:	00008e94 	muleq	r0, r4, lr
    8ea0:	00008e94 	muleq	r0, r4, lr
    8ea4:	00008e9c 	muleq	r0, ip, lr
    8ea8:	00008e9c 	muleq	r0, ip, lr
    8eac:	00008ea4 	andeq	r8, r0, r4, lsr #29
    8eb0:	00008ea4 	andeq	r8, r0, r4, lsr #29
    8eb4:	00008eac 	andeq	r8, r0, ip, lsr #29
    8eb8:	00008eac 	andeq	r8, r0, ip, lsr #29
    8ebc:	00008eb4 			; <UNDEFINED> instruction: 0x00008eb4
    8ec0:	00008eb4 			; <UNDEFINED> instruction: 0x00008eb4
    8ec4:	00008ebc 			; <UNDEFINED> instruction: 0x00008ebc
    8ec8:	00008ebc 			; <UNDEFINED> instruction: 0x00008ebc
    8ecc:	00008ec4 	andeq	r8, r0, r4, asr #29
    8ed0:	00008ec4 	andeq	r8, r0, r4, asr #29
    8ed4:	00008ecc 	andeq	r8, r0, ip, asr #29
    8ed8:	00008ecc 	andeq	r8, r0, ip, asr #29
    8edc:	00008ed4 	ldrdeq	r8, [r0], -r4
    8ee0:	00008ed4 	ldrdeq	r8, [r0], -r4
    8ee4:	00008edc 	ldrdeq	r8, [r0], -ip
    8ee8:	00008edc 	ldrdeq	r8, [r0], -ip
    8eec:	00008ee4 	andeq	r8, r0, r4, ror #29
    8ef0:	00008ee4 	andeq	r8, r0, r4, ror #29
    8ef4:	00008eec 	andeq	r8, r0, ip, ror #29
    8ef8:	00008eec 	andeq	r8, r0, ip, ror #29
    8efc:	00008ef4 	strdeq	r8, [r0], -r4
    8f00:	00008ef4 	strdeq	r8, [r0], -r4
    8f04:	00008efc 	strdeq	r8, [r0], -ip
    8f08:	00008efc 	strdeq	r8, [r0], -ip
    8f0c:	00008f04 	andeq	r8, r0, r4, lsl #30
    8f10:	00008f04 	andeq	r8, r0, r4, lsl #30
    8f14:	00008f0c 	andeq	r8, r0, ip, lsl #30
    8f18:	00008f0c 	andeq	r8, r0, ip, lsl #30
    8f1c:	00008f14 	andeq	r8, r0, r4, lsl pc
    8f20:	00008f14 	andeq	r8, r0, r4, lsl pc
    8f24:	00008f1c 	andeq	r8, r0, ip, lsl pc
    8f28:	00008f1c 	andeq	r8, r0, ip, lsl pc
    8f2c:	00008f24 	andeq	r8, r0, r4, lsr #30
    8f30:	00008f24 	andeq	r8, r0, r4, lsr #30
    8f34:	00008f2c 	andeq	r8, r0, ip, lsr #30
    8f38:	00008f2c 	andeq	r8, r0, ip, lsr #30
    8f3c:	00008f34 	andeq	r8, r0, r4, lsr pc
    8f40:	00008f34 	andeq	r8, r0, r4, lsr pc
    8f44:	00008f3c 	andeq	r8, r0, ip, lsr pc
    8f48:	00008f3c 	andeq	r8, r0, ip, lsr pc
    8f4c:	00008f44 	andeq	r8, r0, r4, asr #30
    8f50:	00008f44 	andeq	r8, r0, r4, asr #30
    8f54:	00008f4c 	andeq	r8, r0, ip, asr #30
    8f58:	00008f4c 	andeq	r8, r0, ip, asr #30
    8f5c:	00008f54 	andeq	r8, r0, r4, asr pc
    8f60:	00008f54 	andeq	r8, r0, r4, asr pc
    8f64:	00008f5c 	andeq	r8, r0, ip, asr pc
    8f68:	00008f5c 	andeq	r8, r0, ip, asr pc
    8f6c:	00008f64 	andeq	r8, r0, r4, ror #30
    8f70:	00008f64 	andeq	r8, r0, r4, ror #30
    8f74:	00008f6c 	andeq	r8, r0, ip, ror #30
    8f78:	00008f6c 	andeq	r8, r0, ip, ror #30
    8f7c:	00008f74 	andeq	r8, r0, r4, ror pc
    8f80:	00008f74 	andeq	r8, r0, r4, ror pc
    8f84:	00008f7c 	andeq	r8, r0, ip, ror pc
    8f88:	00008f7c 	andeq	r8, r0, ip, ror pc
    8f8c:	00008f84 	andeq	r8, r0, r4, lsl #31
    8f90:	00008f84 	andeq	r8, r0, r4, lsl #31
    8f94:	00008f8c 	andeq	r8, r0, ip, lsl #31
    8f98:	00008f8c 	andeq	r8, r0, ip, lsl #31
    8f9c:	00008f94 	muleq	r0, r4, pc	; <UNPREDICTABLE>
    8fa0:	00008f94 	muleq	r0, r4, pc	; <UNPREDICTABLE>
    8fa4:	00008f9c 	muleq	r0, ip, pc	; <UNPREDICTABLE>
    8fa8:	00008f9c 	muleq	r0, ip, pc	; <UNPREDICTABLE>
    8fac:	00008fa4 	andeq	r8, r0, r4, lsr #31
    8fb0:	00008fa4 	andeq	r8, r0, r4, lsr #31
    8fb4:	00008fac 	andeq	r8, r0, ip, lsr #31
    8fb8:	00008fac 	andeq	r8, r0, ip, lsr #31

00008fbc <__malloc_sbrk_base>:
    8fbc:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff

00008fc0 <__malloc_trim_threshold>:
    8fc0:	00020000 	andeq	r0, r2, r0

00008fc4 <_impure_ptr>:
    8fc4:	00008fc8 	andeq	r8, r0, r8, asr #31

00008fc8 <impure_data>:
    8fc8:	00000000 	andeq	r0, r0, r0
    8fcc:	000092b4 			; <UNDEFINED> instruction: 0x000092b4
    8fd0:	0000931c 	andeq	r9, r0, ip, lsl r3
    8fd4:	00009384 	andeq	r9, r0, r4, lsl #7
	...
    9070:	00000001 	andeq	r0, r0, r1
    9074:	00000000 	andeq	r0, r0, r0
    9078:	abcd330e 	blge	ff355cb8 <_stack+0xff2d5cb8>
    907c:	e66d1234 			; <UNDEFINED> instruction: 0xe66d1234
    9080:	0005deec 	andeq	sp, r5, ip, ror #29
    9084:	0000000b 	andeq	r0, r0, fp
	...

Disassembly of section .bss:

000093f0 <heap_end.5685>:
    93f0:	00000000 	andeq	r0, r0, r0

000093f4 <__malloc_current_mallinfo>:
	...

0000941c <__malloc_max_sbrked_mem>:
    941c:	00000000 	andeq	r0, r0, r0

00009420 <__malloc_max_total_mem>:
    9420:	00000000 	andeq	r0, r0, r0

00009424 <__malloc_top_pad>:
    9424:	00000000 	andeq	r0, r0, r0

00009428 <__lock___atexit_recursive_mutex>:
    9428:	00000000 	andeq	r0, r0, r0

0000942c <__lock___arc4random_mutex>:
    942c:	00000000 	andeq	r0, r0, r0

00009430 <__lock___env_recursive_mutex>:
    9430:	00000000 	andeq	r0, r0, r0

00009434 <__lock___sinit_recursive_mutex>:
    9434:	00000000 	andeq	r0, r0, r0

00009438 <__lock___malloc_recursive_mutex>:
    9438:	00000000 	andeq	r0, r0, r0

0000943c <__lock___at_quick_exit_mutex>:
    943c:	00000000 	andeq	r0, r0, r0

00009440 <__lock___dd_hash_mutex>:
    9440:	00000000 	andeq	r0, r0, r0

00009444 <__lock___tz_mutex>:
    9444:	00000000 	andeq	r0, r0, r0

00009448 <__lock___sfp_recursive_mutex>:
    9448:	00000000 	andeq	r0, r0, r0

0000944c <errno>:
    944c:	00000000 	andeq	r0, r0, r0

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <_stack+0x1050d24>
   4:	4e472820 	cdpmi	8, 4, cr2, cr7, cr0, {1}
   8:	6f542055 	svcvs	0x00542055
   c:	20736c6f 	rsbscs	r6, r3, pc, ror #24
  10:	20726f66 	rsbscs	r6, r2, r6, ror #30
  14:	204d5241 	subcs	r5, sp, r1, asr #4
  18:	65626d45 	strbvs	r6, [r2, #-3397]!	; 0xfffff2bb
  1c:	64656464 	strbtvs	r6, [r5], #-1124	; 0xfffffb9c
  20:	6f725020 	svcvs	0x00725020
  24:	73736563 	cmnvc	r3, #415236096	; 0x18c00000
  28:	2073726f 	rsbscs	r7, r3, pc, ror #4
  2c:	30322d36 	eorscc	r2, r2, r6, lsr sp
  30:	712d3731 			; <UNDEFINED> instruction: 0x712d3731
  34:	70752d32 	rsbsvc	r2, r5, r2, lsr sp
  38:	65746164 	ldrbvs	r6, [r4, #-356]!	; 0xfffffe9c
  3c:	2e362029 	cdpcs	0, 3, cr2, cr6, cr9, {1}
  40:	20312e33 	eorscs	r2, r1, r3, lsr lr
  44:	37313032 			; <UNDEFINED> instruction: 0x37313032
  48:	30323630 	eorscc	r3, r2, r0, lsr r6
  4c:	65722820 	ldrbvs	r2, [r2, #-2080]!	; 0xfffff7e0
  50:	7361656c 	cmnvc	r1, #108, 10	; 0x1b000000
  54:	5b202965 	blpl	80a5f0 <_stack+0x78a5f0>
  58:	2f4d5241 	svccs	0x004d5241
  5c:	65626d65 	strbvs	r6, [r2, #-3429]!	; 0xfffff29b
  60:	64656464 	strbtvs	r6, [r5], #-1124	; 0xfffffb9c
  64:	622d362d 	eorvs	r3, sp, #47185920	; 0x2d00000
  68:	636e6172 	cmnvs	lr, #-2147483620	; 0x8000001c
  6c:	65722068 	ldrbvs	r2, [r2, #-104]!	; 0xffffff98
  70:	69736976 	ldmdbvs	r3!, {r1, r2, r4, r5, r6, r8, fp, sp, lr}^
  74:	32206e6f 	eorcc	r6, r0, #1776	; 0x6f0
  78:	33343934 	teqcc	r4, #52, 18	; 0xd0000
  7c:	Address 0x0000007c is out of bounds.


Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	0000800c 	andeq	r8, r0, ip
  14:	0000016c 	andeq	r0, r0, ip, ror #2
	...
  20:	0000001c 	andeq	r0, r0, ip, lsl r0
  24:	09230002 	stmdbeq	r3!, {r1}
  28:	00040000 	andeq	r0, r4, r0
  2c:	00000000 	andeq	r0, r0, r0
  30:	00008178 	andeq	r8, r0, r8, ror r1
  34:	0000007c 	andeq	r0, r0, ip, ror r0
	...
  40:	0000001c 	andeq	r0, r0, ip, lsl r0
  44:	12490002 	subne	r0, r9, #2
  48:	00040000 	andeq	r0, r4, r0
  4c:	00000000 	andeq	r0, r0, r0
  50:	000081f4 	strdeq	r8, [r0], -r4
  54:	0000006c 	andeq	r0, r0, ip, rrx
	...
  60:	0000001c 	andeq	r0, r0, ip, lsl r0
  64:	12f20002 	rscsne	r0, r2, #2
  68:	00040000 	andeq	r0, r4, r0
  6c:	00000000 	andeq	r0, r0, r0
  70:	00008000 	andeq	r8, r0, r0
  74:	0000000c 	andeq	r0, r0, ip
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
       0:	0000091f 	andeq	r0, r0, pc, lsl r9
       4:	00000004 	andeq	r0, r0, r4
       8:	01040000 	mrseq	r0, (UNDEF: 4)
       c:	000001a7 	andeq	r0, r0, r7, lsr #3
      10:	0000760c 	andeq	r7, r0, ip, lsl #12
      14:	00013900 	andeq	r3, r1, r0, lsl #18
      18:	00800c00 	addeq	r0, r0, r0, lsl #24
      1c:	00016c00 	andeq	r6, r1, r0, lsl #24
      20:	00000000 	andeq	r0, r0, r0
      24:	05040200 	streq	r0, [r4, #-512]	; 0xfffffe00
      28:	00746e69 	rsbseq	r6, r4, r9, ror #28
      2c:	55070403 	strpl	r0, [r7, #-1027]	; 0xfffffbfd
      30:	04000000 	streq	r0, [r0], #-0
      34:	0000002c 	andeq	r0, r0, ip, lsr #32
      38:	97050803 	strls	r0, [r5, -r3, lsl #16]
      3c:	03000000 	movweq	r0, #0
      40:	02eb0408 	rsceq	r0, fp, #8, 8	; 0x8000000
      44:	01030000 	mrseq	r0, (UNDEF: 3)
      48:	00034506 	andeq	r4, r3, r6, lsl #10
      4c:	08010300 	stmdaeq	r1, {r8, r9}
      50:	00000343 	andeq	r0, r0, r3, asr #6
      54:	5f050203 	svcpl	0x00050203
      58:	03000003 	movweq	r0, #3
      5c:	02620702 	rsbeq	r0, r2, #524288	; 0x80000
      60:	04030000 	streq	r0, [r3], #-0
      64:	00009c05 	andeq	r9, r0, r5, lsl #24
      68:	07040300 	streq	r0, [r4, -r0, lsl #6]
      6c:	00000050 	andeq	r0, r0, r0, asr r0
      70:	4b070803 	blmi	1c2084 <_stack+0x142084>
      74:	05000000 	streq	r0, [r0, #-0]
      78:	000002b1 			; <UNDEFINED> instruction: 0x000002b1
      7c:	00822202 	addeq	r2, r2, r2, lsl #4
      80:	04060000 	streq	r0, [r6], #-0
      84:	00000088 	andeq	r0, r0, r8, lsl #1
      88:	00040d07 	andeq	r0, r4, r7, lsl #26
      8c:	03240500 			; <UNDEFINED> instruction: 0x03240500
      90:	2c030000 	stccs	0, cr0, [r3], {-0}
      94:	00000062 	andeq	r0, r0, r2, rrx
      98:	00042205 	andeq	r2, r4, r5, lsl #4
      9c:	62720300 	rsbsvs	r0, r2, #0, 6
      a0:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
      a4:	000002b9 			; <UNDEFINED> instruction: 0x000002b9
      a8:	2c016504 	cfstr32cs	mvfx6, [r1], {4}
      ac:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
      b0:	cea60304 	cdpgt	3, 10, cr0, cr6, cr4, {0}
      b4:	0a000000 	beq	bc <_start-0x7f44>
      b8:	000002ab 	andeq	r0, r0, fp, lsr #5
      bc:	00a3a803 	adceq	sl, r3, r3, lsl #16
      c0:	390a0000 	stmdbcc	sl, {}	; <UNPREDICTABLE>
      c4:	03000002 	movweq	r0, #2
      c8:	0000cea9 	andeq	ip, r0, r9, lsr #29
      cc:	4d0b0000 	stcmi	0, cr0, [fp, #-0]
      d0:	de000000 	cdple	0, 0, cr0, cr0, cr0, {0}
      d4:	0c000000 	stceq	0, cr0, [r0], {-0}
      d8:	000000de 	ldrdeq	r0, [r0], -lr
      dc:	04030003 	streq	r0, [r3], #-3
      e0:	0002e207 	andeq	lr, r2, r7, lsl #4
      e4:	03080d00 	movweq	r0, #36096	; 0x8d00
      e8:	000106a3 	andeq	r0, r1, r3, lsr #13
      ec:	04050e00 	streq	r0, [r5], #-3584	; 0xfffff200
      f0:	a5030000 	strge	r0, [r3, #-0]
      f4:	00000025 	andeq	r0, r0, r5, lsr #32
      f8:	04140e00 	ldreq	r0, [r4], #-3584	; 0xfffff200
      fc:	aa030000 	bge	c0104 <_stack+0x40104>
     100:	000000af 	andeq	r0, r0, pc, lsr #1
     104:	87050004 	strhi	r0, [r5, -r4]
     108:	03000003 	movweq	r0, #3
     10c:	0000e5ab 	andeq	lr, r0, fp, lsr #11
     110:	016a0500 	cmneq	sl, r0, lsl #10
     114:	af030000 	svcge	0x00030000
     118:	00000077 	andeq	r0, r0, r7, ror r0
     11c:	0406040f 	streq	r0, [r6], #-1039	; 0xfffffbf1
     120:	00000124 	andeq	r0, r0, r4, lsr #2
     124:	4c080103 	stfmis	f0, [r8], {3}
     128:	10000003 	andne	r0, r0, r3
     12c:	00000124 	andeq	r0, r0, r4, lsr #2
     130:	00045405 	andeq	r5, r4, r5, lsl #8
     134:	69160500 	ldmdbvs	r6, {r8, sl}
     138:	11000000 	mrsne	r0, (UNDEF: 0)
     13c:	0000017b 	andeq	r0, r0, fp, ror r1
     140:	8e2f0518 	mcrhi	5, 1, r0, cr15, cr8, {0}
     144:	0e000001 	cdpeq	0, 0, cr0, cr0, cr1, {0}
     148:	000003a8 	andeq	r0, r0, r8, lsr #7
     14c:	018e3105 	orreq	r3, lr, r5, lsl #2
     150:	12000000 	andne	r0, r0, #0
     154:	05006b5f 	streq	r6, [r0, #-2911]	; 0xfffff4a1
     158:	00002532 	andeq	r2, r0, r2, lsr r5
     15c:	f00e0400 			; <UNDEFINED> instruction: 0xf00e0400
     160:	05000003 	streq	r0, [r0, #-3]
     164:	00002532 	andeq	r2, r0, r2, lsr r5
     168:	640e0800 	strvs	r0, [lr], #-2048	; 0xfffff800
     16c:	05000001 	streq	r0, [r0, #-1]
     170:	00002532 	andeq	r2, r0, r2, lsr r5
     174:	890e0c00 	stmdbhi	lr, {sl, fp}
     178:	05000004 	streq	r0, [r0, #-4]
     17c:	00002532 	andeq	r2, r0, r2, lsr r5
     180:	5f121000 	svcpl	0x00121000
     184:	33050078 	movwcc	r0, #20600	; 0x5078
     188:	00000194 	muleq	r0, r4, r1
     18c:	04060014 	streq	r0, [r6], #-20	; 0xffffffec
     190:	0000013b 	andeq	r0, r0, fp, lsr r1
     194:	0001300b 	andeq	r3, r1, fp
     198:	0001a400 	andeq	sl, r1, r0, lsl #8
     19c:	00de0c00 	sbcseq	r0, lr, r0, lsl #24
     1a0:	00000000 	andeq	r0, r0, r0
     1a4:	0001a211 	andeq	sl, r1, r1, lsl r2
     1a8:	37052400 	strcc	r2, [r5, -r0, lsl #8]
     1ac:	0000021d 	andeq	r0, r0, sp, lsl r2
     1b0:	00008e0e 	andeq	r8, r0, lr, lsl #28
     1b4:	25390500 	ldrcs	r0, [r9, #-1280]!	; 0xfffffb00
     1b8:	00000000 	andeq	r0, r0, r0
     1bc:	00042a0e 	andeq	r2, r4, lr, lsl #20
     1c0:	253a0500 	ldrcs	r0, [sl, #-1280]!	; 0xfffffb00
     1c4:	04000000 	streq	r0, [r0], #-0
     1c8:	0000b10e 	andeq	fp, r0, lr, lsl #2
     1cc:	253b0500 	ldrcs	r0, [fp, #-1280]!	; 0xfffffb00
     1d0:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
     1d4:	00050d0e 	andeq	r0, r5, lr, lsl #26
     1d8:	253c0500 	ldrcs	r0, [ip, #-1280]!	; 0xfffffb00
     1dc:	0c000000 	stceq	0, cr0, [r0], {-0}
     1e0:	0002fe0e 	andeq	pc, r2, lr, lsl #28
     1e4:	253d0500 	ldrcs	r0, [sp, #-1280]!	; 0xfffffb00
     1e8:	10000000 	andne	r0, r0, r0
     1ec:	0002d80e 	andeq	sp, r2, lr, lsl #16
     1f0:	253e0500 	ldrcs	r0, [lr, #-1280]!	; 0xfffffb00
     1f4:	14000000 	strne	r0, [r0], #-0
     1f8:	00048e0e 	andeq	r8, r4, lr, lsl #28
     1fc:	253f0500 	ldrcs	r0, [pc, #-1280]!	; fffffd04 <_stack+0xfff7fd04>
     200:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
     204:	0003690e 	andeq	r6, r3, lr, lsl #18
     208:	25400500 	strbcs	r0, [r0, #-1280]	; 0xfffffb00
     20c:	1c000000 	stcne	0, cr0, [r0], {-0}
     210:	0004d40e 	andeq	sp, r4, lr, lsl #8
     214:	25410500 	strbcs	r0, [r1, #-1280]	; 0xfffffb00
     218:	20000000 	andcs	r0, r0, r0
     21c:	00c01300 	sbceq	r1, r0, r0, lsl #6
     220:	01080000 	mrseq	r0, (UNDEF: 8)
     224:	025d4a05 	subseq	r4, sp, #20480	; 0x5000
     228:	2c0e0000 	stccs	0, cr0, [lr], {-0}
     22c:	05000001 	streq	r0, [r0, #-1]
     230:	00025d4b 	andeq	r5, r2, fp, asr #26
     234:	000e0000 	andeq	r0, lr, r0
     238:	05000000 	streq	r0, [r0, #-0]
     23c:	00025d4c 	andeq	r5, r2, ip, asr #26
     240:	46148000 	ldrmi	r8, [r4], -r0
     244:	05000004 	streq	r0, [r0, #-4]
     248:	0001304e 	andeq	r3, r1, lr, asr #32
     24c:	14010000 	strne	r0, [r1], #-0
     250:	000000e5 	andeq	r0, r0, r5, ror #1
     254:	01305105 	teqeq	r0, r5, lsl #2
     258:	01040000 	mrseq	r0, (UNDEF: 4)
     25c:	011c0b00 	tsteq	ip, r0, lsl #22
     260:	026d0000 	rsbeq	r0, sp, #0
     264:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     268:	1f000000 	svcne	0x00000000
     26c:	03071300 	movweq	r1, #29440	; 0x7300
     270:	01900000 	orrseq	r0, r0, r0
     274:	02ab5d05 	adceq	r5, fp, #320	; 0x140
     278:	a80e0000 	stmdage	lr, {}	; <UNPREDICTABLE>
     27c:	05000003 	streq	r0, [r0, #-3]
     280:	0002ab5e 	andeq	sl, r2, lr, asr fp
     284:	c00e0000 	andgt	r0, lr, r0
     288:	05000003 	streq	r0, [r0, #-3]
     28c:	0000255f 	andeq	r2, r0, pc, asr r5
     290:	340e0400 	strcc	r0, [lr], #-1024	; 0xfffffc00
     294:	05000001 	streq	r0, [r0, #-1]
     298:	0002b161 	andeq	fp, r2, r1, ror #2
     29c:	c00e0800 	andgt	r0, lr, r0, lsl #16
     2a0:	05000000 	streq	r0, [r0, #-0]
     2a4:	00021d62 	andeq	r1, r2, r2, ror #26
     2a8:	06008800 	streq	r8, [r0], -r0, lsl #16
     2ac:	00026d04 	andeq	r6, r2, r4, lsl #26
     2b0:	02c10b00 	sbceq	r0, r1, #0, 22
     2b4:	02c10000 	sbceq	r0, r1, #0
     2b8:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     2bc:	1f000000 	svcne	0x00000000
     2c0:	c7040600 	strgt	r0, [r4, -r0, lsl #12]
     2c4:	15000002 	strne	r0, [r0, #-2]
     2c8:	00037311 	andeq	r7, r3, r1, lsl r3
     2cc:	75050800 	strvc	r0, [r5, #-2048]	; 0xfffff800
     2d0:	000002ed 	andeq	r0, r0, sp, ror #5
     2d4:	0000ab0e 	andeq	sl, r0, lr, lsl #22
     2d8:	ed760500 	cfldr64	mvdx0, [r6, #-0]
     2dc:	00000002 	andeq	r0, r0, r2
     2e0:	00000c0e 	andeq	r0, r0, lr, lsl #24
     2e4:	25770500 	ldrbcs	r0, [r7, #-1280]!	; 0xfffffb00
     2e8:	04000000 	streq	r0, [r0], #-0
     2ec:	4d040600 	stcmi	6, cr0, [r4, #-0]
     2f0:	11000000 	mrsne	r0, (UNDEF: 0)
     2f4:	00000392 	muleq	r0, r2, r3
     2f8:	1db50568 	cfldr32ne	mvfx0, [r5, #416]!	; 0x1a0
     2fc:	12000004 	andne	r0, r0, #4
     300:	0500705f 	streq	r7, [r0, #-95]	; 0xffffffa1
     304:	0002edb6 			; <UNDEFINED> instruction: 0x0002edb6
     308:	5f120000 	svcpl	0x00120000
     30c:	b7050072 	smlsdxlt	r5, r2, r0, r0
     310:	00000025 	andeq	r0, r0, r5, lsr #32
     314:	775f1204 	ldrbvc	r1, [pc, -r4, lsl #4]
     318:	25b80500 	ldrcs	r0, [r8, #1280]!	; 0x500
     31c:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
     320:	0000de0e 	andeq	sp, r0, lr, lsl #28
     324:	54b90500 	ldrtpl	r0, [r9], #1280	; 0x500
     328:	0c000000 	stceq	0, cr0, [r0], {-0}
     32c:	0002550e 	andeq	r5, r2, lr, lsl #10
     330:	54ba0500 	ldrtpl	r0, [sl], #1280	; 0x500
     334:	0e000000 	cdpeq	0, 0, cr0, cr0, cr0, {0}
     338:	66625f12 	uqadd16vs	r5, r2, r2
     33c:	c8bb0500 	ldmgt	fp!, {r8, sl}
     340:	10000002 	andne	r0, r0, r2
     344:	0000620e 	andeq	r6, r0, lr, lsl #4
     348:	25bc0500 	ldrcs	r0, [ip, #1280]!	; 0x500
     34c:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
     350:	0000ce0e 	andeq	ip, r0, lr, lsl #28
     354:	1cc30500 	cfstr64ne	mvdx0, [r3], {0}
     358:	1c000001 	stcne	0, cr0, [r0], {1}
     35c:	0001920e 	andeq	r9, r1, lr, lsl #4
     360:	78c50500 	stmiavc	r5, {r8, sl}^
     364:	20000005 	andcs	r0, r0, r5
     368:	0002d10e 	andeq	sp, r2, lr, lsl #2
     36c:	a2c70500 	sbcge	r0, r7, #0, 10
     370:	24000005 	strcs	r0, [r0], #-5
     374:	00041c0e 	andeq	r1, r4, lr, lsl #24
     378:	c6ca0500 	strbgt	r0, [sl], r0, lsl #10
     37c:	28000005 	stmdacs	r0, {r0, r2}
     380:	0004ee0e 	andeq	lr, r4, lr, lsl #28
     384:	e0cb0500 	sbc	r0, fp, r0, lsl #10
     388:	2c000005 	stccs	0, cr0, [r0], {5}
     38c:	62755f12 	rsbsvs	r5, r5, #18, 30	; 0x48
     390:	c8ce0500 	stmiagt	lr, {r8, sl}^
     394:	30000002 	andcc	r0, r0, r2
     398:	70755f12 	rsbsvc	r5, r5, r2, lsl pc
     39c:	edcf0500 	cfstr64	mvdx0, [pc]	; 3a4 <_start-0x7c5c>
     3a0:	38000002 	stmdacc	r0, {r1}
     3a4:	72755f12 	rsbsvc	r5, r5, #18, 30	; 0x48
     3a8:	25d00500 	ldrbcs	r0, [r0, #1280]	; 0x500
     3ac:	3c000000 	stccc	0, cr0, [r0], {-0}
     3b0:	0000a50e 	andeq	sl, r0, lr, lsl #10
     3b4:	e6d30500 	ldrb	r0, [r3], r0, lsl #10
     3b8:	40000005 	andmi	r0, r0, r5
     3bc:	0004c60e 	andeq	ip, r4, lr, lsl #12
     3c0:	f6d40500 			; <UNDEFINED> instruction: 0xf6d40500
     3c4:	43000005 	movwmi	r0, #5
     3c8:	626c5f12 	rsbvs	r5, ip, #18, 30	; 0x48
     3cc:	c8d70500 	ldmgt	r7, {r8, sl}^
     3d0:	44000002 	strmi	r0, [r0], #-2
     3d4:	0000f40e 	andeq	pc, r0, lr, lsl #8
     3d8:	25da0500 	ldrbcs	r0, [sl, #1280]	; 0x500
     3dc:	4c000000 	stcmi	0, cr0, [r0], {-0}
     3e0:	0001050e 	andeq	r0, r1, lr, lsl #10
     3e4:	8ddb0500 	cfldr64hi	mvdx0, [fp]
     3e8:	50000000 	andpl	r0, r0, r0
     3ec:	0000250e 	andeq	r2, r0, lr, lsl #10
     3f0:	3bde0500 	blcc	ff7817f8 <_stack+0xff7017f8>
     3f4:	54000004 	strpl	r0, [r0], #-4
     3f8:	00040e0e 	andeq	r0, r4, lr, lsl #28
     3fc:	11e20500 	mvnne	r0, r0, lsl #10
     400:	58000001 	stmdapl	r0, {r0}
     404:	00039a0e 	andeq	r9, r3, lr, lsl #20
     408:	06e40500 	strbteq	r0, [r4], r0, lsl #10
     40c:	5c000001 	stcpl	0, cr0, [r0], {1}
     410:	0002c00e 	andeq	ip, r2, lr
     414:	25e50500 	strbcs	r0, [r5, #1280]!	; 0x500
     418:	64000000 	strvs	r0, [r0], #-0
     41c:	00251600 	eoreq	r1, r5, r0, lsl #12
     420:	043b0000 	ldrteq	r0, [fp], #-0
     424:	3b170000 	blcc	5c042c <_stack+0x54042c>
     428:	17000004 	strne	r0, [r0, -r4]
     42c:	0000011c 	andeq	r0, r0, ip, lsl r1
     430:	00011e17 	andeq	r1, r1, r7, lsl lr
     434:	00251700 	eoreq	r1, r5, r0, lsl #14
     438:	06000000 	streq	r0, [r0], -r0
     43c:	00044604 	andeq	r4, r4, r4, lsl #12
     440:	043b1000 	ldrteq	r1, [fp], #-0
     444:	f8180000 			; <UNDEFINED> instruction: 0xf8180000
     448:	28000003 	stmdacs	r0, {r0, r1}
     44c:	02390504 	eorseq	r0, r9, #4, 10	; 0x1000000
     450:	00000578 	andeq	r0, r0, r8, ror r5
     454:	00035819 	andeq	r5, r3, r9, lsl r8
     458:	023b0500 	eorseq	r0, fp, #0, 10
     45c:	00000025 	andeq	r0, r0, r5, lsr #32
     460:	00ed1900 	rsceq	r1, sp, r0, lsl #18
     464:	40050000 	andmi	r0, r5, r0
     468:	00064d02 	andeq	r4, r6, r2, lsl #26
     46c:	40190400 	andsmi	r0, r9, r0, lsl #8
     470:	05000002 	streq	r0, [r0, #-2]
     474:	064d0240 	strbeq	r0, [sp], -r0, asr #4
     478:	19080000 	stmdbne	r8, {}	; <UNPREDICTABLE>
     47c:	00000173 	andeq	r0, r0, r3, ror r1
     480:	4d024005 	stcmi	0, cr4, [r2, #-20]	; 0xffffffec
     484:	0c000006 	stceq	0, cr0, [r0], {6}
     488:	0003bb19 	andeq	fp, r3, r9, lsl fp
     48c:	02420500 	subeq	r0, r2, #0, 10
     490:	00000025 	andeq	r0, r0, r5, lsr #32
     494:	001a1910 	andseq	r1, sl, r0, lsl r9
     498:	43050000 	movwmi	r0, #20480	; 0x5000
     49c:	00082f02 	andeq	r2, r8, r2, lsl #30
     4a0:	d7191400 	ldrle	r1, [r9, -r0, lsl #8]
     4a4:	05000003 	streq	r0, [r0, #-3]
     4a8:	00250246 	eoreq	r0, r5, r6, asr #4
     4ac:	19300000 	ldmdbne	r0!, {}	; <UNPREDICTABLE>
     4b0:	000003c5 	andeq	r0, r0, r5, asr #7
     4b4:	44024705 	strmi	r4, [r2], #-1797	; 0xfffff8fb
     4b8:	34000008 	strcc	r0, [r0], #-8
     4bc:	00031919 	andeq	r1, r3, r9, lsl r9
     4c0:	02490500 	subeq	r0, r9, #0, 10
     4c4:	00000025 	andeq	r0, r0, r5, lsr #32
     4c8:	03cd1938 	biceq	r1, sp, #56, 18	; 0xe0000
     4cc:	4b050000 	blmi	1404d4 <_stack+0xc04d4>
     4d0:	00085502 	andeq	r5, r8, r2, lsl #10
     4d4:	a3193c00 	tstge	r9, #0, 24
     4d8:	05000002 	streq	r0, [r0, #-2]
     4dc:	018e024e 	orreq	r0, lr, lr, asr #4
     4e0:	19400000 	stmdbne	r0, {}^	; <UNPREDICTABLE>
     4e4:	00000198 	muleq	r0, r8, r1
     4e8:	25024f05 	strcs	r4, [r2, #-3845]	; 0xfffff0fb
     4ec:	44000000 	strmi	r0, [r0], #-0
     4f0:	00050819 	andeq	r0, r5, r9, lsl r8
     4f4:	02500500 	subseq	r0, r0, #0, 10
     4f8:	0000018e 	andeq	r0, r0, lr, lsl #3
     4fc:	032b1948 			; <UNDEFINED> instruction: 0x032b1948
     500:	51050000 	mrspl	r0, (UNDEF: 5)
     504:	00085b02 	andeq	r5, r8, r2, lsl #22
     508:	4d194c00 	ldcmi	12, cr4, [r9, #-0]
     50c:	05000002 	streq	r0, [r0, #-2]
     510:	00250254 	eoreq	r0, r5, r4, asr r2
     514:	19500000 	ldmdbne	r0, {}^	; <UNPREDICTABLE>
     518:	000000fd 	strdeq	r0, [r0], -sp
     51c:	1e025505 	cfsh32ne	mvfx5, mvfx2, #5
     520:	54000001 	strpl	r0, [r0], #-1
     524:	00035119 	andeq	r5, r3, r9, lsl r1
     528:	02780500 	rsbseq	r0, r8, #0, 10
     52c:	0000080d 	andeq	r0, r0, sp, lsl #16
     530:	03071a58 	movweq	r1, #31320	; 0x7a58
     534:	7c050000 	stcvc	0, cr0, [r5], {-0}
     538:	0002ab02 	andeq	sl, r2, r2, lsl #22
     53c:	1a014800 	bne	52544 <__bss_end__+0x490f4>
     540:	00000275 	andeq	r0, r0, r5, ror r2
     544:	6d027d05 	stcvs	13, cr7, [r2, #-20]	; 0xffffffec
     548:	4c000002 	stcmi	0, cr0, [r0], {2}
     54c:	04b11a01 	ldrteq	r1, [r1], #2561	; 0xa01
     550:	81050000 	mrshi	r0, (UNDEF: 5)
     554:	00086c02 	andeq	r6, r8, r2, lsl #24
     558:	1a02dc00 	bne	b7560 <_stack+0x37560>
     55c:	000000d6 	ldrdeq	r0, [r0], -r6
     560:	12028605 	andne	r8, r2, #5242880	; 0x500000
     564:	e0000006 	and	r0, r0, r6
     568:	00bb1a02 	adcseq	r1, fp, r2, lsl #20
     56c:	87050000 	strhi	r0, [r5, -r0]
     570:	00087802 	andeq	r7, r8, r2, lsl #16
     574:	0002ec00 	andeq	lr, r2, r0, lsl #24
     578:	041d0406 	ldreq	r0, [sp], #-1030	; 0xfffffbfa
     57c:	25160000 	ldrcs	r0, [r6, #-0]
     580:	9c000000 	stcls	0, cr0, [r0], {-0}
     584:	17000005 	strne	r0, [r0, -r5]
     588:	0000043b 	andeq	r0, r0, fp, lsr r4
     58c:	00011c17 	andeq	r1, r1, r7, lsl ip
     590:	059c1700 	ldreq	r1, [ip, #1792]	; 0x700
     594:	25170000 	ldrcs	r0, [r7, #-0]
     598:	00000000 	andeq	r0, r0, r0
     59c:	012b0406 			; <UNDEFINED> instruction: 0x012b0406
     5a0:	04060000 	streq	r0, [r6], #-0
     5a4:	0000057e 	andeq	r0, r0, lr, ror r5
     5a8:	00009816 	andeq	r9, r0, r6, lsl r8
     5ac:	0005c600 	andeq	ip, r5, r0, lsl #12
     5b0:	043b1700 	ldrteq	r1, [fp], #-1792	; 0xfffff900
     5b4:	1c170000 	ldcne	0, cr0, [r7], {-0}
     5b8:	17000001 	strne	r0, [r0, -r1]
     5bc:	00000098 	muleq	r0, r8, r0
     5c0:	00002517 	andeq	r2, r0, r7, lsl r5
     5c4:	04060000 	streq	r0, [r6], #-0
     5c8:	000005a8 	andeq	r0, r0, r8, lsr #11
     5cc:	00002516 	andeq	r2, r0, r6, lsl r5
     5d0:	0005e000 	andeq	lr, r5, r0
     5d4:	043b1700 	ldrteq	r1, [fp], #-1792	; 0xfffff900
     5d8:	1c170000 	ldcne	0, cr0, [r7], {-0}
     5dc:	00000001 	andeq	r0, r0, r1
     5e0:	05cc0406 	strbeq	r0, [ip, #1030]	; 0x406
     5e4:	4d0b0000 	stcmi	0, cr0, [fp, #-0]
     5e8:	f6000000 			; <UNDEFINED> instruction: 0xf6000000
     5ec:	0c000005 	stceq	0, cr0, [r0], {5}
     5f0:	000000de 	ldrdeq	r0, [r0], -lr
     5f4:	4d0b0002 	stcmi	0, cr0, [fp, #-8]
     5f8:	06000000 	streq	r0, [r0], -r0
     5fc:	0c000006 	stceq	0, cr0, [r0], {6}
     600:	000000de 	ldrdeq	r0, [r0], -lr
     604:	80080000 	andhi	r0, r8, r0
     608:	05000003 	streq	r0, [r0, #-3]
     60c:	02f3011f 	rscseq	r0, r3, #-1073741817	; 0xc0000007
     610:	981b0000 	ldmdals	fp, {}	; <UNPREDICTABLE>
     614:	0c000004 	stceq	0, cr0, [r0], {4}
     618:	47012305 	strmi	r2, [r1, -r5, lsl #6]
     61c:	19000006 	stmdbne	r0, {r1, r2}
     620:	000003a8 	andeq	r0, r0, r8, lsr #7
     624:	47012505 	strmi	r2, [r1, -r5, lsl #10]
     628:	00000006 	andeq	r0, r0, r6
     62c:	00025b19 	andeq	r5, r2, r9, lsl fp
     630:	01260500 			; <UNDEFINED> instruction: 0x01260500
     634:	00000025 	andeq	r0, r0, r5, lsr #32
     638:	037a1904 	cmneq	sl, #4, 18	; 0x10000
     63c:	27050000 	strcs	r0, [r5, -r0]
     640:	00064d01 	andeq	r4, r6, r1, lsl #26
     644:	06000800 	streq	r0, [r0], -r0, lsl #16
     648:	00061204 	andeq	r1, r6, r4, lsl #4
     64c:	06040600 	streq	r0, [r4], -r0, lsl #12
     650:	1b000006 	blne	670 <_start-0x7990>
     654:	00000012 	andeq	r0, r0, r2, lsl r0
     658:	013f050e 	teqeq	pc, lr, lsl #10
     65c:	00000688 	andeq	r0, r0, r8, lsl #13
     660:	0003ff19 	andeq	pc, r3, r9, lsl pc	; <UNPREDICTABLE>
     664:	01400500 	cmpeq	r0, r0, lsl #10
     668:	00000688 	andeq	r0, r0, r8, lsl #13
     66c:	04331900 	ldrteq	r1, [r3], #-2304	; 0xfffff700
     670:	41050000 	mrsmi	r0, (UNDEF: 5)
     674:	00068801 	andeq	r8, r6, r1, lsl #16
     678:	4f190600 	svcmi	0x00190600
     67c:	05000004 	streq	r0, [r0, #-4]
     680:	005b0142 	subseq	r0, fp, r2, asr #2
     684:	000c0000 	andeq	r0, ip, r0
     688:	00005b0b 	andeq	r5, r0, fp, lsl #22
     68c:	00069800 	andeq	r9, r6, r0, lsl #16
     690:	00de0c00 	sbcseq	r0, lr, r0, lsl #24
     694:	00020000 	andeq	r0, r2, r0
     698:	5905d01c 	stmdbpl	r5, {r2, r3, r4, ip, lr, pc}
     69c:	00079902 	andeq	r9, r7, r2, lsl #18
     6a0:	047c1900 	ldrbteq	r1, [ip], #-2304	; 0xfffff700
     6a4:	5b050000 	blpl	1406ac <_stack+0xc06ac>
     6a8:	00002c02 	andeq	r2, r0, r2, lsl #24
     6ac:	39190000 	ldmdbcc	r9, {}	; <UNPREDICTABLE>
     6b0:	05000004 	streq	r0, [r0, #-4]
     6b4:	011e025c 	tsteq	lr, ip, asr r2
     6b8:	19040000 	stmdbne	r4, {}	; <UNPREDICTABLE>
     6bc:	00000296 	muleq	r0, r6, r2
     6c0:	99025d05 	stmdbls	r2, {r0, r2, r8, sl, fp, ip, lr}
     6c4:	08000007 	stmdaeq	r0, {r0, r1, r2}
     6c8:	0004df19 	andeq	sp, r4, r9, lsl pc
     6cc:	025e0500 	subseq	r0, lr, #0, 10
     6d0:	000001a4 	andeq	r0, r0, r4, lsr #3
     6d4:	01831924 	orreq	r1, r3, r4, lsr #18
     6d8:	5f050000 	svcpl	0x00050000
     6dc:	00002502 	andeq	r2, r0, r2, lsl #10
     6e0:	a3194800 	tstge	r9, #0, 16
     6e4:	05000003 	streq	r0, [r0, #-3]
     6e8:	00700260 	rsbseq	r0, r0, r0, ror #4
     6ec:	19500000 	ldmdbne	r0, {}^	; <UNPREDICTABLE>
     6f0:	000004f5 	strdeq	r0, [r0], -r5
     6f4:	53026105 	movwpl	r6, #8453	; 0x2105
     6f8:	58000006 	stmdapl	r0, {r1, r2}
     6fc:	0003ae19 	andeq	sl, r3, r9, lsl lr
     700:	02620500 	rsbeq	r0, r2, #0, 10
     704:	00000106 	andeq	r0, r0, r6, lsl #2
     708:	04fa1968 	ldrbteq	r1, [sl], #2408	; 0x968
     70c:	63050000 	movwvs	r0, #20480	; 0x5000
     710:	00010602 	andeq	r0, r1, r2, lsl #12
     714:	35197000 	ldrcc	r7, [r9, #-0]
     718:	05000003 	streq	r0, [r0, #-3]
     71c:	01060264 	tsteq	r6, r4, ror #4
     720:	19780000 	ldmdbne	r8!, {}^	; <UNPREDICTABLE>
     724:	000004a7 	andeq	r0, r0, r7, lsr #9
     728:	a9026505 	stmdbge	r2, {r0, r2, r8, sl, sp, lr}
     72c:	80000007 	andhi	r0, r0, r7
     730:	00028a19 	andeq	r8, r2, r9, lsl sl
     734:	02660500 	rsbeq	r0, r6, #0, 10
     738:	000007b9 			; <UNDEFINED> instruction: 0x000007b9
     73c:	045c1988 	ldrbeq	r1, [ip], #-2440	; 0xfffff678
     740:	67050000 	strvs	r0, [r5, -r0]
     744:	00002502 	andeq	r2, r0, r2, lsl #10
     748:	1e19a000 	cdpne	0, 1, cr10, cr9, cr0, {0}
     74c:	05000001 	streq	r0, [r0, #-1]
     750:	01060268 	tsteq	r6, r8, ror #4
     754:	19a40000 	stmibne	r4!, {}	; <UNPREDICTABLE>
     758:	0000007f 	andeq	r0, r0, pc, ror r0
     75c:	06026905 	streq	r6, [r2], -r5, lsl #18
     760:	ac000001 	stcge	0, cr0, [r0], {1}
     764:	00010d19 	andeq	r0, r1, r9, lsl sp
     768:	026a0500 	rsbeq	r0, sl, #0, 10
     76c:	00000106 	andeq	r0, r0, r6, lsl #2
     770:	002b19b4 	strhteq	r1, [fp], -r4
     774:	6b050000 	blvs	14077c <_stack+0xc077c>
     778:	00010602 	andeq	r0, r1, r2, lsl #12
     77c:	3a19bc00 	bcc	66f784 <_stack+0x5ef784>
     780:	05000000 	streq	r0, [r0, #-0]
     784:	0106026c 	tsteq	r6, ip, ror #4
     788:	19c40000 	stmibne	r4, {}^	; <UNPREDICTABLE>
     78c:	00000356 	andeq	r0, r0, r6, asr r3
     790:	25026d05 	strcs	r6, [r2, #-3333]	; 0xfffff2fb
     794:	cc000000 	stcgt	0, cr0, [r0], {-0}
     798:	01240b00 			; <UNDEFINED> instruction: 0x01240b00
     79c:	07a90000 	streq	r0, [r9, r0]!
     7a0:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     7a4:	19000000 	stmdbne	r0, {}	; <UNPREDICTABLE>
     7a8:	01240b00 			; <UNDEFINED> instruction: 0x01240b00
     7ac:	07b90000 	ldreq	r0, [r9, r0]!
     7b0:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     7b4:	07000000 	streq	r0, [r0, -r0]
     7b8:	01240b00 			; <UNDEFINED> instruction: 0x01240b00
     7bc:	07c90000 	strbeq	r0, [r9, r0]
     7c0:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     7c4:	17000000 	strne	r0, [r0, -r0]
     7c8:	05f01c00 	ldrbeq	r1, [r0, #3072]!	; 0xc00
     7cc:	07ed0272 			; <UNDEFINED> instruction: 0x07ed0272
     7d0:	f7190000 			; <UNDEFINED> instruction: 0xf7190000
     7d4:	05000002 	streq	r0, [r0, #-2]
     7d8:	07ed0275 			; <UNDEFINED> instruction: 0x07ed0275
     7dc:	19000000 	stmdbne	r0, {}	; <UNPREDICTABLE>
     7e0:	0000049e 	muleq	r0, lr, r4
     7e4:	fd027605 	stc2	6, cr7, [r2, #-20]	; 0xffffffec
     7e8:	78000007 	stmdavc	r0, {r0, r1, r2}
     7ec:	02ed0b00 	rsceq	r0, sp, #0, 22
     7f0:	07fd0000 	ldrbeq	r0, [sp, r0]!
     7f4:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     7f8:	1d000000 	stcne	0, cr0, [r0, #-0]
     7fc:	002c0b00 	eoreq	r0, ip, r0, lsl #22
     800:	080d0000 	stmdaeq	sp, {}	; <UNPREDICTABLE>
     804:	de0c0000 	cdple	0, 0, cr0, cr12, cr0, {0}
     808:	1d000000 	stcne	0, cr0, [r0, #-0]
     80c:	05f01d00 	ldrbeq	r1, [r0, #3328]!	; 0xd00
     810:	082f0257 	stmdaeq	pc!, {r0, r1, r2, r4, r6, r9}	; <UNPREDICTABLE>
     814:	f81e0000 			; <UNDEFINED> instruction: 0xf81e0000
     818:	05000003 	streq	r0, [r0, #-3]
     81c:	0698026e 	ldreq	r0, [r8], lr, ror #4
     820:	cc1e0000 	ldcgt	0, cr0, [lr], {-0}
     824:	05000004 	streq	r0, [r0, #-4]
     828:	07c90277 			; <UNDEFINED> instruction: 0x07c90277
     82c:	0b000000 	bleq	834 <_start-0x77cc>
     830:	00000124 	andeq	r0, r0, r4, lsr #2
     834:	0000083f 	andeq	r0, r0, pc, lsr r8
     838:	0000de0c 	andeq	sp, r0, ip, lsl #28
     83c:	07001800 	streq	r1, [r0, -r0, lsl #16]
     840:	0000006b 	andeq	r0, r0, fp, rrx
     844:	083f0406 	ldmdaeq	pc!, {r1, r2, sl}	; <UNPREDICTABLE>
     848:	551f0000 	ldrpl	r0, [pc, #-0]	; 850 <_start-0x77b0>
     84c:	17000008 	strne	r0, [r0, -r8]
     850:	0000043b 	andeq	r0, r0, fp, lsr r4
     854:	4a040600 	bmi	10205c <_stack+0x8205c>
     858:	06000008 	streq	r0, [r0], -r8
     85c:	00018e04 	andeq	r8, r1, r4, lsl #28
     860:	086c1f00 	stmdaeq	ip!, {r8, r9, sl, fp, ip}^
     864:	25170000 	ldrcs	r0, [r7, #-0]
     868:	00000000 	andeq	r0, r0, r0
     86c:	08720406 	ldmdaeq	r2!, {r1, r2, sl}^
     870:	04060000 	streq	r0, [r6], #-0
     874:	00000861 	andeq	r0, r0, r1, ror #16
     878:	0006060b 	andeq	r0, r6, fp, lsl #12
     87c:	00088800 	andeq	r8, r8, r0, lsl #16
     880:	00de0c00 	sbcseq	r0, lr, r0, lsl #24
     884:	00020000 	andeq	r0, r2, r0
     888:	00047020 	andeq	r7, r4, r0, lsr #32
     88c:	02fe0500 	rscseq	r0, lr, #0, 10
     890:	0000043b 	andeq	r0, r0, fp, lsr r4
     894:	00046920 	andeq	r6, r4, r0, lsr #18
     898:	02ff0500 	rscseq	r0, pc, #0, 10
     89c:	00000441 	andeq	r0, r0, r1, asr #8
     8a0:	00030f21 	andeq	r0, r3, r1, lsr #30
     8a4:	1e630600 	cdpne	6, 6, cr0, cr3, cr0, {0}
     8a8:	22000001 	andcs	r0, r0, #1
     8ac:	000004c1 	andeq	r0, r0, r1, asr #9
     8b0:	08bc0701 	ldmeq	ip!, {r0, r8, r9, sl}
     8b4:	03050000 	movweq	r0, #20480	; 0x5000
     8b8:	00008bb0 			; <UNDEFINED> instruction: 0x00008bb0
     8bc:	00330406 	eorseq	r0, r3, r6, lsl #8
     8c0:	7e230000 	cdpvc	0, 2, cr0, cr3, cr0, {0}
     8c4:	01000002 	tsteq	r0, r2
     8c8:	00800c0a 	addeq	r0, r0, sl, lsl #24
     8cc:	00016c00 	andeq	r6, r1, r0, lsl #24
     8d0:	1c9c0100 	ldfnes	f0, [ip], {0}
     8d4:	24000009 	strcs	r0, [r0], #-9
     8d8:	01003072 	tsteq	r0, r2, ror r0
     8dc:	00002c0a 	andeq	r2, r0, sl, lsl #24
     8e0:	6c910200 	lfmvs	f0, 4, [r1], {0}
     8e4:	00317224 	eorseq	r7, r1, r4, lsr #4
     8e8:	002c0a01 	eoreq	r0, ip, r1, lsl #20
     8ec:	91020000 	mrsls	r0, (UNDEF: 2)
     8f0:	04bb2568 	ldrteq	r2, [fp], #1384	; 0x568
     8f4:	0a010000 	beq	408fc <__bss_end__+0x374ac>
     8f8:	0000002c 	andeq	r0, r0, ip, lsr #32
     8fc:	26649102 	strbtcs	r9, [r4], -r2, lsl #2
     900:	00000248 	andeq	r0, r0, r8, asr #4
     904:	00250c01 	eoreq	r0, r5, r1, lsl #24
     908:	91020000 	mrsls	r0, (UNDEF: 2)
     90c:	02c82674 	sbceq	r2, r8, #116, 12	; 0x7400000
     910:	0d010000 	stceq	0, cr0, [r1, #-0]
     914:	0000091c 	andeq	r0, r0, ip, lsl r9
     918:	00709102 	rsbseq	r9, r0, r2, lsl #2
     91c:	002c0406 	eoreq	r0, ip, r6, lsl #8
     920:	22000000 	andcs	r0, r0, #0
     924:	04000009 	streq	r0, [r0], #-9
     928:	0001ee00 	andeq	lr, r1, r0, lsl #28
     92c:	a7010400 	strge	r0, [r1, -r0, lsl #8]
     930:	0c000001 	stceq	0, cr0, [r0], {1}
     934:	00000521 	andeq	r0, r0, r1, lsr #10
     938:	00000139 	andeq	r0, r0, r9, lsr r1
     93c:	00008178 	andeq	r8, r0, r8, ror r1
     940:	0000007c 	andeq	r0, r0, ip, ror r0
     944:	000001aa 	andeq	r0, r0, sl, lsr #3
     948:	45060102 	strmi	r0, [r6, #-258]	; 0xfffffefe
     94c:	02000003 	andeq	r0, r0, #3
     950:	03430801 	movteq	r0, #14337	; 0x3801
     954:	02020000 	andeq	r0, r2, #0
     958:	00035f05 	andeq	r5, r3, r5, lsl #30
     95c:	07020200 	streq	r0, [r2, -r0, lsl #4]
     960:	00000262 	andeq	r0, r0, r2, ror #4
     964:	9c050402 	cfstrsls	mvf0, [r5], {2}
     968:	02000000 	andeq	r0, r0, #0
     96c:	00500704 	subseq	r0, r0, r4, lsl #14
     970:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
     974:	00009705 	andeq	r9, r0, r5, lsl #14
     978:	07080200 	streq	r0, [r8, -r0, lsl #4]
     97c:	0000004b 	andeq	r0, r0, fp, asr #32
     980:	69050403 	stmdbvs	r5, {r0, r1, sl}
     984:	0200746e 	andeq	r7, r0, #1845493760	; 0x6e000000
     988:	00550704 	subseq	r0, r5, r4, lsl #14
     98c:	08020000 	stmdaeq	r2, {}	; <UNPREDICTABLE>
     990:	0002eb04 	andeq	lr, r2, r4, lsl #22
     994:	02b10400 	adcseq	r0, r1, #0, 8
     998:	22020000 	andcs	r0, r2, #0
     99c:	0000007d 	andeq	r0, r0, sp, ror r0
     9a0:	00830405 	addeq	r0, r3, r5, lsl #8
     9a4:	0d060000 	stceq	0, cr0, [r6, #-0]
     9a8:	04000004 	streq	r0, [r0], #-4
     9ac:	00000324 	andeq	r0, r0, r4, lsr #6
     9b0:	00412c03 	subeq	r2, r1, r3, lsl #24
     9b4:	22040000 	andcs	r0, r4, #0
     9b8:	03000004 	movweq	r0, #4
     9bc:	00004172 	andeq	r4, r0, r2, ror r1
     9c0:	02b90700 	adcseq	r0, r9, #0, 14
     9c4:	65040000 	strvs	r0, [r4, #-0]
     9c8:	00006401 	andeq	r6, r0, r1, lsl #8
     9cc:	03040800 	movweq	r0, #18432	; 0x4800
     9d0:	0000c9a6 	andeq	ip, r0, r6, lsr #19
     9d4:	02ab0900 	adceq	r0, fp, #0, 18
     9d8:	a8030000 	stmdage	r3, {}	; <UNPREDICTABLE>
     9dc:	0000009e 	muleq	r0, lr, r0
     9e0:	00023909 	andeq	r3, r2, r9, lsl #18
     9e4:	c9a90300 	stmibgt	r9!, {r8, r9}
     9e8:	00000000 	andeq	r0, r0, r0
     9ec:	00002c0a 	andeq	r2, r0, sl, lsl #24
     9f0:	0000d900 	andeq	sp, r0, r0, lsl #18
     9f4:	00d90b00 	sbcseq	r0, r9, r0, lsl #22
     9f8:	00030000 	andeq	r0, r3, r0
     9fc:	e2070402 	and	r0, r7, #33554432	; 0x2000000
     a00:	0c000002 	stceq	0, cr0, [r0], {2}
     a04:	01a30308 			; <UNDEFINED> instruction: 0x01a30308
     a08:	0d000001 	stceq	0, cr0, [r0, #-4]
     a0c:	00000405 	andeq	r0, r0, r5, lsl #8
     a10:	005da503 	subseq	sl, sp, r3, lsl #10
     a14:	0d000000 	stceq	0, cr0, [r0, #-0]
     a18:	00000414 	andeq	r0, r0, r4, lsl r4
     a1c:	00aaaa03 	adceq	sl, sl, r3, lsl #20
     a20:	00040000 	andeq	r0, r4, r0
     a24:	00038704 	andeq	r8, r3, r4, lsl #14
     a28:	e0ab0300 	adc	r0, fp, r0, lsl #6
     a2c:	04000000 	streq	r0, [r0], #-0
     a30:	0000016a 	andeq	r0, r0, sl, ror #2
     a34:	0072af03 	rsbseq	sl, r2, r3, lsl #30
     a38:	040e0000 	streq	r0, [lr], #-0
     a3c:	00045404 	andeq	r5, r4, r4, lsl #8
     a40:	48160500 	ldmdami	r6, {r8, sl}
     a44:	0f000000 	svceq	0x00000000
     a48:	0000017b 	andeq	r0, r0, fp, ror r1
     a4c:	772f0518 			; <UNDEFINED> instruction: 0x772f0518
     a50:	0d000001 	stceq	0, cr0, [r0, #-4]
     a54:	000003a8 	andeq	r0, r0, r8, lsr #7
     a58:	01773105 	cmneq	r7, r5, lsl #2
     a5c:	10000000 	andne	r0, r0, r0
     a60:	05006b5f 	streq	r6, [r0, #-2911]	; 0xfffff4a1
     a64:	00005d32 	andeq	r5, r0, r2, lsr sp
     a68:	f00d0400 			; <UNDEFINED> instruction: 0xf00d0400
     a6c:	05000003 	streq	r0, [r0, #-3]
     a70:	00005d32 	andeq	r5, r0, r2, lsr sp
     a74:	640d0800 	strvs	r0, [sp], #-2048	; 0xfffff800
     a78:	05000001 	streq	r0, [r0, #-1]
     a7c:	00005d32 	andeq	r5, r0, r2, lsr sp
     a80:	890d0c00 	stmdbhi	sp, {sl, fp}
     a84:	05000004 	streq	r0, [r0, #-4]
     a88:	00005d32 	andeq	r5, r0, r2, lsr sp
     a8c:	5f101000 	svcpl	0x00101000
     a90:	33050078 	movwcc	r0, #20600	; 0x5078
     a94:	0000017d 	andeq	r0, r0, sp, ror r1
     a98:	04050014 	streq	r0, [r5], #-20	; 0xffffffec
     a9c:	00000124 	andeq	r0, r0, r4, lsr #2
     aa0:	0001190a 	andeq	r1, r1, sl, lsl #18
     aa4:	00018d00 	andeq	r8, r1, r0, lsl #26
     aa8:	00d90b00 	sbcseq	r0, r9, r0, lsl #22
     aac:	00000000 	andeq	r0, r0, r0
     ab0:	0001a20f 	andeq	sl, r1, pc, lsl #4
     ab4:	37052400 	strcc	r2, [r5, -r0, lsl #8]
     ab8:	00000206 	andeq	r0, r0, r6, lsl #4
     abc:	00008e0d 	andeq	r8, r0, sp, lsl #28
     ac0:	5d390500 	cfldr32pl	mvfx0, [r9, #-0]
     ac4:	00000000 	andeq	r0, r0, r0
     ac8:	00042a0d 	andeq	r2, r4, sp, lsl #20
     acc:	5d3a0500 	cfldr32pl	mvfx0, [sl, #-0]
     ad0:	04000000 	streq	r0, [r0], #-0
     ad4:	0000b10d 	andeq	fp, r0, sp, lsl #2
     ad8:	5d3b0500 	cfldr32pl	mvfx0, [fp, #-0]
     adc:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
     ae0:	00050d0d 	andeq	r0, r5, sp, lsl #26
     ae4:	5d3c0500 	cfldr32pl	mvfx0, [ip, #-0]
     ae8:	0c000000 	stceq	0, cr0, [r0], {-0}
     aec:	0002fe0d 	andeq	pc, r2, sp, lsl #28
     af0:	5d3d0500 	cfldr32pl	mvfx0, [sp, #-0]
     af4:	10000000 	andne	r0, r0, r0
     af8:	0002d80d 	andeq	sp, r2, sp, lsl #16
     afc:	5d3e0500 	cfldr32pl	mvfx0, [lr, #-0]
     b00:	14000000 	strne	r0, [r0], #-0
     b04:	00048e0d 	andeq	r8, r4, sp, lsl #28
     b08:	5d3f0500 	cfldr32pl	mvfx0, [pc, #-0]	; b10 <_start-0x74f0>
     b0c:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
     b10:	0003690d 	andeq	r6, r3, sp, lsl #18
     b14:	5d400500 	cfstr64pl	mvdx0, [r0, #-0]
     b18:	1c000000 	stcne	0, cr0, [r0], {-0}
     b1c:	0004d40d 	andeq	sp, r4, sp, lsl #8
     b20:	5d410500 	cfstr64pl	mvdx0, [r1, #-0]
     b24:	20000000 	andcs	r0, r0, r0
     b28:	00c01100 	sbceq	r1, r0, r0, lsl #2
     b2c:	01080000 	mrseq	r0, (UNDEF: 8)
     b30:	02464a05 	subeq	r4, r6, #20480	; 0x5000
     b34:	2c0d0000 	stccs	0, cr0, [sp], {-0}
     b38:	05000001 	streq	r0, [r0, #-1]
     b3c:	0002464b 	andeq	r4, r2, fp, asr #12
     b40:	000d0000 	andeq	r0, sp, r0
     b44:	05000000 	streq	r0, [r0, #-0]
     b48:	0002464c 	andeq	r4, r2, ip, asr #12
     b4c:	46128000 	ldrmi	r8, [r2], -r0
     b50:	05000004 	streq	r0, [r0, #-4]
     b54:	0001194e 	andeq	r1, r1, lr, asr #18
     b58:	12010000 	andne	r0, r1, #0
     b5c:	000000e5 	andeq	r0, r0, r5, ror #1
     b60:	01195105 	tsteq	r9, r5, lsl #2
     b64:	01040000 	mrseq	r0, (UNDEF: 4)
     b68:	01170a00 	tsteq	r7, r0, lsl #20
     b6c:	02560000 	subseq	r0, r6, #0
     b70:	d90b0000 	stmdble	fp, {}	; <UNPREDICTABLE>
     b74:	1f000000 	svcne	0x00000000
     b78:	03071100 	movweq	r1, #28928	; 0x7100
     b7c:	01900000 	orrseq	r0, r0, r0
     b80:	02945d05 	addseq	r5, r4, #320	; 0x140
     b84:	a80d0000 	stmdage	sp, {}	; <UNPREDICTABLE>
     b88:	05000003 	streq	r0, [r0, #-3]
     b8c:	0002945e 	andeq	r9, r2, lr, asr r4
     b90:	c00d0000 	andgt	r0, sp, r0
     b94:	05000003 	streq	r0, [r0, #-3]
     b98:	00005d5f 	andeq	r5, r0, pc, asr sp
     b9c:	340d0400 	strcc	r0, [sp], #-1024	; 0xfffffc00
     ba0:	05000001 	streq	r0, [r0, #-1]
     ba4:	00029a61 	andeq	r9, r2, r1, ror #20
     ba8:	c00d0800 	andgt	r0, sp, r0, lsl #16
     bac:	05000000 	streq	r0, [r0, #-0]
     bb0:	00020662 	andeq	r0, r2, r2, ror #12
     bb4:	05008800 	streq	r8, [r0, #-2048]	; 0xfffff800
     bb8:	00025604 	andeq	r5, r2, r4, lsl #12
     bbc:	02aa0a00 	adceq	r0, sl, #0, 20
     bc0:	02aa0000 	adceq	r0, sl, #0
     bc4:	d90b0000 	stmdble	fp, {}	; <UNPREDICTABLE>
     bc8:	1f000000 	svcne	0x00000000
     bcc:	b0040500 	andlt	r0, r4, r0, lsl #10
     bd0:	13000002 	movwne	r0, #2
     bd4:	0003730f 	andeq	r7, r3, pc, lsl #6
     bd8:	75050800 	strvc	r0, [r5, #-2048]	; 0xfffff800
     bdc:	000002d6 	ldrdeq	r0, [r0], -r6
     be0:	0000ab0d 	andeq	sl, r0, sp, lsl #22
     be4:	d6760500 	ldrbtle	r0, [r6], -r0, lsl #10
     be8:	00000002 	andeq	r0, r0, r2
     bec:	00000c0d 	andeq	r0, r0, sp, lsl #24
     bf0:	5d770500 	cfldr64pl	mvdx0, [r7, #-0]
     bf4:	04000000 	streq	r0, [r0], #-0
     bf8:	2c040500 	cfstr32cs	mvfx0, [r4], {-0}
     bfc:	0f000000 	svceq	0x00000000
     c00:	00000392 	muleq	r0, r2, r3
     c04:	06b50568 	ldrteq	r0, [r5], r8, ror #10
     c08:	10000004 	andne	r0, r0, r4
     c0c:	0500705f 	streq	r7, [r0, #-95]	; 0xffffffa1
     c10:	0002d6b6 			; <UNDEFINED> instruction: 0x0002d6b6
     c14:	5f100000 	svcpl	0x00100000
     c18:	b7050072 	smlsdxlt	r5, r2, r0, r0
     c1c:	0000005d 	andeq	r0, r0, sp, asr r0
     c20:	775f1004 	ldrbvc	r1, [pc, -r4]
     c24:	5db80500 	cfldr32pl	mvfx0, [r8]
     c28:	08000000 	stmdaeq	r0, {}	; <UNPREDICTABLE>
     c2c:	0000de0d 	andeq	sp, r0, sp, lsl #28
     c30:	33b90500 			; <UNDEFINED> instruction: 0x33b90500
     c34:	0c000000 	stceq	0, cr0, [r0], {-0}
     c38:	0002550d 	andeq	r5, r2, sp, lsl #10
     c3c:	33ba0500 			; <UNDEFINED> instruction: 0x33ba0500
     c40:	0e000000 	cdpeq	0, 0, cr0, cr0, cr0, {0}
     c44:	66625f10 	uqadd16vs	r5, r2, r0
     c48:	b1bb0500 			; <UNDEFINED> instruction: 0xb1bb0500
     c4c:	10000002 	andne	r0, r0, r2
     c50:	0000620d 	andeq	r6, r0, sp, lsl #4
     c54:	5dbc0500 	cfldr32pl	mvfx0, [ip]
     c58:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
     c5c:	0000ce0d 	andeq	ip, r0, sp, lsl #28
     c60:	17c30500 	strbne	r0, [r3, r0, lsl #10]
     c64:	1c000001 	stcne	0, cr0, [r0], {1}
     c68:	0001920d 	andeq	r9, r1, sp, lsl #4
     c6c:	73c50500 	bicvc	r0, r5, #0, 10
     c70:	20000005 	andcs	r0, r0, r5
     c74:	0002d10d 	andeq	sp, r2, sp, lsl #2
     c78:	9dc70500 	cfstr64ls	mvdx0, [r7]
     c7c:	24000005 	strcs	r0, [r0], #-5
     c80:	00041c0d 	andeq	r1, r4, sp, lsl #24
     c84:	c1ca0500 	bicgt	r0, sl, r0, lsl #10
     c88:	28000005 	stmdacs	r0, {r0, r2}
     c8c:	0004ee0d 	andeq	lr, r4, sp, lsl #28
     c90:	dbcb0500 	blle	ff2c2098 <_stack+0xff242098>
     c94:	2c000005 	stccs	0, cr0, [r0], {5}
     c98:	62755f10 	rsbsvs	r5, r5, #16, 30	; 0x40
     c9c:	b1ce0500 	biclt	r0, lr, r0, lsl #10
     ca0:	30000002 	andcc	r0, r0, r2
     ca4:	70755f10 	rsbsvc	r5, r5, r0, lsl pc
     ca8:	d6cf0500 	strble	r0, [pc], r0, lsl #10
     cac:	38000002 	stmdacc	r0, {r1}
     cb0:	72755f10 	rsbsvc	r5, r5, #16, 30	; 0x40
     cb4:	5dd00500 	cfldr64pl	mvdx0, [r0]
     cb8:	3c000000 	stccc	0, cr0, [r0], {-0}
     cbc:	0000a50d 	andeq	sl, r0, sp, lsl #10
     cc0:	e1d30500 	bics	r0, r3, r0, lsl #10
     cc4:	40000005 	andmi	r0, r0, r5
     cc8:	0004c60d 	andeq	ip, r4, sp, lsl #12
     ccc:	f1d40500 			; <UNDEFINED> instruction: 0xf1d40500
     cd0:	43000005 	movwmi	r0, #5
     cd4:	626c5f10 	rsbvs	r5, ip, #16, 30	; 0x40
     cd8:	b1d70500 	bicslt	r0, r7, r0, lsl #10
     cdc:	44000002 	strmi	r0, [r0], #-2
     ce0:	0000f40d 	andeq	pc, r0, sp, lsl #8
     ce4:	5dda0500 	cfldr64pl	mvdx0, [sl]
     ce8:	4c000000 	stcmi	0, cr0, [r0], {-0}
     cec:	0001050d 	andeq	r0, r1, sp, lsl #10
     cf0:	88db0500 	ldmhi	fp, {r8, sl}^
     cf4:	50000000 	andpl	r0, r0, r0
     cf8:	0000250d 	andeq	r2, r0, sp, lsl #10
     cfc:	24de0500 	ldrbcs	r0, [lr], #1280	; 0x500
     d00:	54000004 	strpl	r0, [r0], #-4
     d04:	00040e0d 	andeq	r0, r4, sp, lsl #28
     d08:	0ce20500 	cfstr64eq	mvdx0, [r2]
     d0c:	58000001 	stmdapl	r0, {r0}
     d10:	00039a0d 	andeq	r9, r3, sp, lsl #20
     d14:	01e40500 	mvneq	r0, r0, lsl #10
     d18:	5c000001 	stcpl	0, cr0, [r0], {1}
     d1c:	0002c00d 	andeq	ip, r2, sp
     d20:	5de50500 	cfstr64pl	mvdx0, [r5]
     d24:	64000000 	strvs	r0, [r0], #-0
     d28:	005d1400 	subseq	r1, sp, r0, lsl #8
     d2c:	04240000 	strteq	r0, [r4], #-0
     d30:	24150000 	ldrcs	r0, [r5], #-0
     d34:	15000004 	strne	r0, [r0, #-4]
     d38:	00000117 	andeq	r0, r0, r7, lsl r1
     d3c:	00056115 	andeq	r6, r5, r5, lsl r1
     d40:	005d1500 	subseq	r1, sp, r0, lsl #10
     d44:	05000000 	streq	r0, [r0, #-0]
     d48:	00042f04 	andeq	r2, r4, r4, lsl #30
     d4c:	04241600 	strteq	r1, [r4], #-1536	; 0xfffffa00
     d50:	f8170000 			; <UNDEFINED> instruction: 0xf8170000
     d54:	28000003 	stmdacs	r0, {r0, r1}
     d58:	02390504 	eorseq	r0, r9, #4, 10	; 0x1000000
     d5c:	00000561 	andeq	r0, r0, r1, ror #10
     d60:	00035818 	andeq	r5, r3, r8, lsl r8
     d64:	023b0500 	eorseq	r0, fp, #0, 10
     d68:	0000005d 	andeq	r0, r0, sp, asr r0
     d6c:	00ed1800 	rsceq	r1, sp, r0, lsl #16
     d70:	40050000 	andmi	r0, r5, r0
     d74:	00064802 	andeq	r4, r6, r2, lsl #16
     d78:	40180400 	andsmi	r0, r8, r0, lsl #8
     d7c:	05000002 	streq	r0, [r0, #-2]
     d80:	06480240 	strbeq	r0, [r8], -r0, asr #4
     d84:	18080000 	stmdane	r8, {}	; <UNPREDICTABLE>
     d88:	00000173 	andeq	r0, r0, r3, ror r1
     d8c:	48024005 	stmdami	r2, {r0, r2, lr}
     d90:	0c000006 	stceq	0, cr0, [r0], {6}
     d94:	0003bb18 	andeq	fp, r3, r8, lsl fp
     d98:	02420500 	subeq	r0, r2, #0, 10
     d9c:	0000005d 	andeq	r0, r0, sp, asr r0
     da0:	001a1810 	andseq	r1, sl, r0, lsl r8
     da4:	43050000 	movwmi	r0, #20480	; 0x5000
     da8:	00082a02 	andeq	r2, r8, r2, lsl #20
     dac:	d7181400 	ldrle	r1, [r8, -r0, lsl #8]
     db0:	05000003 	streq	r0, [r0, #-3]
     db4:	005d0246 	subseq	r0, sp, r6, asr #4
     db8:	18300000 	ldmdane	r0!, {}	; <UNPREDICTABLE>
     dbc:	000003c5 	andeq	r0, r0, r5, asr #7
     dc0:	3f024705 	svccc	0x00024705
     dc4:	34000008 	strcc	r0, [r0], #-8
     dc8:	00031918 	andeq	r1, r3, r8, lsl r9
     dcc:	02490500 	subeq	r0, r9, #0, 10
     dd0:	0000005d 	andeq	r0, r0, sp, asr r0
     dd4:	03cd1838 	biceq	r1, sp, #56, 16	; 0x380000
     dd8:	4b050000 	blmi	140de0 <_stack+0xc0de0>
     ddc:	00085002 	andeq	r5, r8, r2
     de0:	a3183c00 	tstge	r8, #0, 24
     de4:	05000002 	streq	r0, [r0, #-2]
     de8:	0177024e 	cmneq	r7, lr, asr #4
     dec:	18400000 	stmdane	r0, {}^	; <UNPREDICTABLE>
     df0:	00000198 	muleq	r0, r8, r1
     df4:	5d024f05 	stcpl	15, cr4, [r2, #-20]	; 0xffffffec
     df8:	44000000 	strmi	r0, [r0], #-0
     dfc:	00050818 	andeq	r0, r5, r8, lsl r8
     e00:	02500500 	subseq	r0, r0, #0, 10
     e04:	00000177 	andeq	r0, r0, r7, ror r1
     e08:	032b1848 			; <UNDEFINED> instruction: 0x032b1848
     e0c:	51050000 	mrspl	r0, (UNDEF: 5)
     e10:	00085602 	andeq	r5, r8, r2, lsl #12
     e14:	4d184c00 	ldcmi	12, cr4, [r8, #-0]
     e18:	05000002 	streq	r0, [r0, #-2]
     e1c:	005d0254 	subseq	r0, sp, r4, asr r2
     e20:	18500000 	ldmdane	r0, {}^	; <UNPREDICTABLE>
     e24:	000000fd 	strdeq	r0, [r0], -sp
     e28:	61025505 	tstvs	r2, r5, lsl #10
     e2c:	54000005 	strpl	r0, [r0], #-5
     e30:	00035118 	andeq	r5, r3, r8, lsl r1
     e34:	02780500 	rsbseq	r0, r8, #0, 10
     e38:	00000808 	andeq	r0, r0, r8, lsl #16
     e3c:	03071958 	movweq	r1, #31064	; 0x7958
     e40:	7c050000 	stcvc	0, cr0, [r5], {-0}
     e44:	00029402 	andeq	r9, r2, r2, lsl #8
     e48:	19014800 	stmdbne	r1, {fp, lr}
     e4c:	00000275 	andeq	r0, r0, r5, ror r2
     e50:	56027d05 	strpl	r7, [r2], -r5, lsl #26
     e54:	4c000002 	stcmi	0, cr0, [r0], {2}
     e58:	04b11901 	ldrteq	r1, [r1], #2305	; 0x901
     e5c:	81050000 	mrshi	r0, (UNDEF: 5)
     e60:	00086702 	andeq	r6, r8, r2, lsl #14
     e64:	1902dc00 	stmdbne	r2, {sl, fp, ip, lr, pc}
     e68:	000000d6 	ldrdeq	r0, [r0], -r6
     e6c:	0d028605 	stceq	6, cr8, [r2, #-20]	; 0xffffffec
     e70:	e0000006 	and	r0, r0, r6
     e74:	00bb1902 	adcseq	r1, fp, r2, lsl #18
     e78:	87050000 	strhi	r0, [r5, -r0]
     e7c:	00087302 	andeq	r7, r8, r2, lsl #6
     e80:	0002ec00 	andeq	lr, r2, r0, lsl #24
     e84:	05670405 	strbeq	r0, [r7, #-1029]!	; 0xfffffbfb
     e88:	01020000 	mrseq	r0, (UNDEF: 2)
     e8c:	00034c08 	andeq	r4, r3, r8, lsl #24
     e90:	05671600 	strbeq	r1, [r7, #-1536]!	; 0xfffffa00
     e94:	04050000 	streq	r0, [r5], #-0
     e98:	00000406 	andeq	r0, r0, r6, lsl #8
     e9c:	00005d14 	andeq	r5, r0, r4, lsl sp
     ea0:	00059700 	andeq	r9, r5, r0, lsl #14
     ea4:	04241500 	strteq	r1, [r4], #-1280	; 0xfffffb00
     ea8:	17150000 	ldrne	r0, [r5, -r0]
     eac:	15000001 	strne	r0, [r0, #-1]
     eb0:	00000597 	muleq	r0, r7, r5
     eb4:	00005d15 	andeq	r5, r0, r5, lsl sp
     eb8:	04050000 	streq	r0, [r5], #-0
     ebc:	0000056e 	andeq	r0, r0, lr, ror #10
     ec0:	05790405 	ldrbeq	r0, [r9, #-1029]!	; 0xfffffbfb
     ec4:	93140000 	tstls	r4, #0
     ec8:	c1000000 	mrsgt	r0, (UNDEF: 0)
     ecc:	15000005 	strne	r0, [r0, #-5]
     ed0:	00000424 	andeq	r0, r0, r4, lsr #8
     ed4:	00011715 	andeq	r1, r1, r5, lsl r7
     ed8:	00931500 	addseq	r1, r3, r0, lsl #10
     edc:	5d150000 	ldcpl	0, cr0, [r5, #-0]
     ee0:	00000000 	andeq	r0, r0, r0
     ee4:	05a30405 	streq	r0, [r3, #1029]!	; 0x405
     ee8:	5d140000 	ldcpl	0, cr0, [r4, #-0]
     eec:	db000000 	blle	ef4 <_start-0x710c>
     ef0:	15000005 	strne	r0, [r0, #-5]
     ef4:	00000424 	andeq	r0, r0, r4, lsr #8
     ef8:	00011715 	andeq	r1, r1, r5, lsl r7
     efc:	04050000 	streq	r0, [r5], #-0
     f00:	000005c7 	andeq	r0, r0, r7, asr #11
     f04:	00002c0a 	andeq	r2, r0, sl, lsl #24
     f08:	0005f100 	andeq	pc, r5, r0, lsl #2
     f0c:	00d90b00 	sbcseq	r0, r9, r0, lsl #22
     f10:	00020000 	andeq	r0, r2, r0
     f14:	00002c0a 	andeq	r2, r0, sl, lsl #24
     f18:	00060100 	andeq	r0, r6, r0, lsl #2
     f1c:	00d90b00 	sbcseq	r0, r9, r0, lsl #22
     f20:	00000000 	andeq	r0, r0, r0
     f24:	00038007 	andeq	r8, r3, r7
     f28:	011f0500 	tsteq	pc, r0, lsl #10
     f2c:	000002dc 	ldrdeq	r0, [r0], -ip
     f30:	0004981a 	andeq	r9, r4, sl, lsl r8
     f34:	23050c00 	movwcs	r0, #23552	; 0x5c00
     f38:	00064201 	andeq	r4, r6, r1, lsl #4
     f3c:	03a81800 			; <UNDEFINED> instruction: 0x03a81800
     f40:	25050000 	strcs	r0, [r5, #-0]
     f44:	00064201 	andeq	r4, r6, r1, lsl #4
     f48:	5b180000 	blpl	600f50 <_stack+0x580f50>
     f4c:	05000002 	streq	r0, [r0, #-2]
     f50:	005d0126 	subseq	r0, sp, r6, lsr #2
     f54:	18040000 	stmdane	r4, {}	; <UNPREDICTABLE>
     f58:	0000037a 	andeq	r0, r0, sl, ror r3
     f5c:	48012705 	stmdami	r1, {r0, r2, r8, r9, sl, sp}
     f60:	08000006 	stmdaeq	r0, {r1, r2}
     f64:	0d040500 	cfstr32eq	mvfx0, [r4, #-0]
     f68:	05000006 	streq	r0, [r0, #-6]
     f6c:	00060104 	andeq	r0, r6, r4, lsl #2
     f70:	00121a00 	andseq	r1, r2, r0, lsl #20
     f74:	050e0000 	streq	r0, [lr, #-0]
     f78:	0683013f 			; <UNDEFINED> instruction: 0x0683013f
     f7c:	ff180000 			; <UNDEFINED> instruction: 0xff180000
     f80:	05000003 	streq	r0, [r0, #-3]
     f84:	06830140 	streq	r0, [r3], r0, asr #2
     f88:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
     f8c:	00000433 	andeq	r0, r0, r3, lsr r4
     f90:	83014105 	movwhi	r4, #4357	; 0x1105
     f94:	06000006 	streq	r0, [r0], -r6
     f98:	00044f18 	andeq	r4, r4, r8, lsl pc
     f9c:	01420500 	cmpeq	r2, r0, lsl #10
     fa0:	0000003a 	andeq	r0, r0, sl, lsr r0
     fa4:	3a0a000c 	bcc	280fdc <_stack+0x200fdc>
     fa8:	93000000 	movwls	r0, #0
     fac:	0b000006 	bleq	fcc <_start-0x7034>
     fb0:	000000d9 	ldrdeq	r0, [r0], -r9
     fb4:	d01b0002 	andsle	r0, fp, r2
     fb8:	94025905 	strls	r5, [r2], #-2309	; 0xfffff6fb
     fbc:	18000007 	stmdane	r0, {r0, r1, r2}
     fc0:	0000047c 	andeq	r0, r0, ip, ror r4
     fc4:	64025b05 	strvs	r5, [r2], #-2821	; 0xfffff4fb
     fc8:	00000000 	andeq	r0, r0, r0
     fcc:	00043918 	andeq	r3, r4, r8, lsl r9
     fd0:	025c0500 	subseq	r0, ip, #0, 10
     fd4:	00000561 	andeq	r0, r0, r1, ror #10
     fd8:	02961804 	addseq	r1, r6, #4, 16	; 0x40000
     fdc:	5d050000 	stcpl	0, cr0, [r5, #-0]
     fe0:	00079402 	andeq	r9, r7, r2, lsl #8
     fe4:	df180800 	svcle	0x00180800
     fe8:	05000004 	streq	r0, [r0, #-4]
     fec:	018d025e 	orreq	r0, sp, lr, asr r2
     ff0:	18240000 	stmdane	r4!, {}	; <UNPREDICTABLE>
     ff4:	00000183 	andeq	r0, r0, r3, lsl #3
     ff8:	5d025f05 	stcpl	15, cr5, [r2, #-20]	; 0xffffffec
     ffc:	48000000 	stmdami	r0, {}	; <UNPREDICTABLE>
    1000:	0003a318 	andeq	sl, r3, r8, lsl r3
    1004:	02600500 	rsbeq	r0, r0, #0, 10
    1008:	00000056 	andeq	r0, r0, r6, asr r0
    100c:	04f51850 	ldrbteq	r1, [r5], #2128	; 0x850
    1010:	61050000 	mrsvs	r0, (UNDEF: 5)
    1014:	00064e02 	andeq	r4, r6, r2, lsl #28
    1018:	ae185800 	cdpge	8, 1, cr5, cr8, cr0, {0}
    101c:	05000003 	streq	r0, [r0, #-3]
    1020:	01010262 	tsteq	r1, r2, ror #4
    1024:	18680000 	stmdane	r8!, {}^	; <UNPREDICTABLE>
    1028:	000004fa 	strdeq	r0, [r0], -sl
    102c:	01026305 	tsteq	r2, r5, lsl #6
    1030:	70000001 	andvc	r0, r0, r1
    1034:	00033518 	andeq	r3, r3, r8, lsl r5
    1038:	02640500 	rsbeq	r0, r4, #0, 10
    103c:	00000101 	andeq	r0, r0, r1, lsl #2
    1040:	04a71878 	strteq	r1, [r7], #2168	; 0x878
    1044:	65050000 	strvs	r0, [r5, #-0]
    1048:	0007a402 	andeq	sl, r7, r2, lsl #8
    104c:	8a188000 	bhi	621054 <_stack+0x5a1054>
    1050:	05000002 	streq	r0, [r0, #-2]
    1054:	07b40266 	ldreq	r0, [r4, r6, ror #4]!
    1058:	18880000 	stmne	r8, {}	; <UNPREDICTABLE>
    105c:	0000045c 	andeq	r0, r0, ip, asr r4
    1060:	5d026705 	stcpl	7, cr6, [r2, #-20]	; 0xffffffec
    1064:	a0000000 	andge	r0, r0, r0
    1068:	00011e18 	andeq	r1, r1, r8, lsl lr
    106c:	02680500 	rsbeq	r0, r8, #0, 10
    1070:	00000101 	andeq	r0, r0, r1, lsl #2
    1074:	007f18a4 	rsbseq	r1, pc, r4, lsr #17
    1078:	69050000 	stmdbvs	r5, {}	; <UNPREDICTABLE>
    107c:	00010102 	andeq	r0, r1, r2, lsl #2
    1080:	0d18ac00 	ldceq	12, cr10, [r8, #-0]
    1084:	05000001 	streq	r0, [r0, #-1]
    1088:	0101026a 	tsteq	r1, sl, ror #4
    108c:	18b40000 	ldmne	r4!, {}	; <UNPREDICTABLE>
    1090:	0000002b 	andeq	r0, r0, fp, lsr #32
    1094:	01026b05 	tsteq	r2, r5, lsl #22
    1098:	bc000001 	stclt	0, cr0, [r0], {1}
    109c:	00003a18 	andeq	r3, r0, r8, lsl sl
    10a0:	026c0500 	rsbeq	r0, ip, #0, 10
    10a4:	00000101 	andeq	r0, r0, r1, lsl #2
    10a8:	035618c4 	cmpeq	r6, #196, 16	; 0xc40000
    10ac:	6d050000 	stcvs	0, cr0, [r5, #-0]
    10b0:	00005d02 	andeq	r5, r0, r2, lsl #26
    10b4:	0a00cc00 	beq	340bc <__bss_end__+0x2ac6c>
    10b8:	00000567 	andeq	r0, r0, r7, ror #10
    10bc:	000007a4 	andeq	r0, r0, r4, lsr #15
    10c0:	0000d90b 	andeq	sp, r0, fp, lsl #18
    10c4:	0a001900 	beq	74cc <_start-0xb34>
    10c8:	00000567 	andeq	r0, r0, r7, ror #10
    10cc:	000007b4 			; <UNDEFINED> instruction: 0x000007b4
    10d0:	0000d90b 	andeq	sp, r0, fp, lsl #18
    10d4:	0a000700 	beq	2cdc <_start-0x5324>
    10d8:	00000567 	andeq	r0, r0, r7, ror #10
    10dc:	000007c4 	andeq	r0, r0, r4, asr #15
    10e0:	0000d90b 	andeq	sp, r0, fp, lsl #18
    10e4:	1b001700 	blne	6cec <_start-0x1314>
    10e8:	027205f0 	rsbseq	r0, r2, #240, 10	; 0x3c000000
    10ec:	000007e8 	andeq	r0, r0, r8, ror #15
    10f0:	0002f718 	andeq	pc, r2, r8, lsl r7	; <UNPREDICTABLE>
    10f4:	02750500 	rsbseq	r0, r5, #0, 10
    10f8:	000007e8 	andeq	r0, r0, r8, ror #15
    10fc:	049e1800 	ldreq	r1, [lr], #2048	; 0x800
    1100:	76050000 	strvc	r0, [r5], -r0
    1104:	0007f802 	andeq	pc, r7, r2, lsl #16
    1108:	0a007800 	beq	1f110 <__bss_end__+0x15cc0>
    110c:	000002d6 	ldrdeq	r0, [r0], -r6
    1110:	000007f8 	strdeq	r0, [r0], -r8
    1114:	0000d90b 	andeq	sp, r0, fp, lsl #18
    1118:	0a001d00 	beq	8520 <_malloc_r+0x2a0>
    111c:	00000064 	andeq	r0, r0, r4, rrx
    1120:	00000808 	andeq	r0, r0, r8, lsl #16
    1124:	0000d90b 	andeq	sp, r0, fp, lsl #18
    1128:	1c001d00 	stcne	13, cr1, [r0], {-0}
    112c:	025705f0 	subseq	r0, r7, #240, 10	; 0x3c000000
    1130:	0000082a 	andeq	r0, r0, sl, lsr #16
    1134:	0003f81d 	andeq	pc, r3, sp, lsl r8	; <UNPREDICTABLE>
    1138:	026e0500 	rsbeq	r0, lr, #0, 10
    113c:	00000693 	muleq	r0, r3, r6
    1140:	0004cc1d 	andeq	ip, r4, sp, lsl ip
    1144:	02770500 	rsbseq	r0, r7, #0, 10
    1148:	000007c4 	andeq	r0, r0, r4, asr #15
    114c:	05670a00 	strbeq	r0, [r7, #-2560]!	; 0xfffff600
    1150:	083a0000 	ldmdaeq	sl!, {}	; <UNPREDICTABLE>
    1154:	d90b0000 	stmdble	fp, {}	; <UNPREDICTABLE>
    1158:	18000000 	stmdane	r0, {}	; <UNPREDICTABLE>
    115c:	006b0600 	rsbeq	r0, fp, r0, lsl #12
    1160:	04050000 	streq	r0, [r5], #-0
    1164:	0000083a 	andeq	r0, r0, sl, lsr r8
    1168:	0008501e 	andeq	r5, r8, lr, lsl r0
    116c:	04241500 	strteq	r1, [r4], #-1280	; 0xfffffb00
    1170:	05000000 	streq	r0, [r0, #-0]
    1174:	00084504 	andeq	r4, r8, r4, lsl #10
    1178:	77040500 	strvc	r0, [r4, -r0, lsl #10]
    117c:	1e000001 	cdpne	0, 0, cr0, cr0, cr1, {0}
    1180:	00000867 	andeq	r0, r0, r7, ror #16
    1184:	00005d15 	andeq	r5, r0, r5, lsl sp
    1188:	04050000 	streq	r0, [r5], #-0
    118c:	0000086d 	andeq	r0, r0, sp, ror #16
    1190:	085c0405 	ldmdaeq	ip, {r0, r2, sl}^
    1194:	010a0000 	mrseq	r0, (UNDEF: 10)
    1198:	83000006 	movwhi	r0, #6
    119c:	0b000008 	bleq	11c4 <_start-0x6e3c>
    11a0:	000000d9 	ldrdeq	r0, [r0], -r9
    11a4:	701f0002 	andsvc	r0, pc, r2
    11a8:	05000004 	streq	r0, [r0, #-4]
    11ac:	042402fe 	strteq	r0, [r4], #-766	; 0xfffffd02
    11b0:	691f0000 	ldmdbvs	pc, {}	; <UNPREDICTABLE>
    11b4:	05000004 	streq	r0, [r0, #-4]
    11b8:	042a02ff 	strteq	r0, [sl], #-767	; 0xfffffd01
    11bc:	57040000 	strpl	r0, [r4, -r0]
    11c0:	06000005 	streq	r0, [r0], -r5
    11c4:	0005618b 	andeq	r6, r5, fp, lsl #3
    11c8:	054d2000 	strbeq	r2, [sp, #-0]
    11cc:	9a070000 	bls	1c11d4 <_stack+0x1411d4>
    11d0:	00000041 	andeq	r0, r0, r1, asr #32
    11d4:	00051720 	andeq	r1, r5, r0, lsr #14
    11d8:	5d9b0700 	ldcpl	7, cr0, [fp]
    11dc:	0a000000 	beq	11e4 <_start-0x6e1c>
    11e0:	00000561 	andeq	r0, r0, r1, ror #10
    11e4:	000008cc 	andeq	r0, r0, ip, asr #17
    11e8:	0000d90b 	andeq	sp, r0, fp, lsl #18
    11ec:	20000100 	andcs	r0, r0, r0, lsl #2
    11f0:	00000532 	andeq	r0, r0, r2, lsr r5
    11f4:	08bc9e07 	ldmeq	ip!, {r0, r1, r2, r9, sl, fp, ip, pc}
    11f8:	5f210000 	svcpl	0x00210000
    11fc:	01000005 	tsteq	r0, r5
    1200:	00089b3f 	andeq	r9, r8, pc, lsr fp
    1204:	00817800 	addeq	r7, r1, r0, lsl #16
    1208:	00007c00 	andeq	r7, r0, r0, lsl #24
    120c:	229c0100 	addscs	r0, ip, #0, 2
    1210:	00000548 	andeq	r0, r0, r8, asr #10
    1214:	005d3f01 	subseq	r3, sp, r1, lsl #30
    1218:	91020000 	mrsls	r0, (UNDEF: 2)
    121c:	0543206c 	strbeq	r2, [r3, #-108]	; 0xffffff94
    1220:	41010000 	mrsmi	r0, (UNDEF: 1)
    1224:	00000567 	andeq	r0, r0, r7, ror #10
    1228:	00053f23 	andeq	r3, r5, r3, lsr #30
    122c:	61420100 	mrsvs	r0, (UNDEF: 82)
    1230:	05000005 	streq	r0, [r0, #-5]
    1234:	0093f003 	addseq	pc, r3, r3
    1238:	053a2300 	ldreq	r2, [sl, #-768]!	; 0xfffffd00
    123c:	43010000 	movwmi	r0, #4096	; 0x1000
    1240:	00000561 	andeq	r0, r0, r1, ror #10
    1244:	00749102 	rsbseq	r9, r4, r2, lsl #2
    1248:	0000a500 	andeq	sl, r0, r0, lsl #10
    124c:	b5000400 	strlt	r0, [r0, #-1024]	; 0xfffffc00
    1250:	04000003 	streq	r0, [r0], #-3
    1254:	0001a701 	andeq	sl, r1, r1, lsl #14
    1258:	057b0c00 	ldrbeq	r0, [fp, #-3072]!	; 0xfffff400
    125c:	01390000 	teqeq	r9, r0
    1260:	81f40000 	mvnshi	r0, r0
    1264:	006c0000 	rsbeq	r0, ip, r0
    1268:	03310000 	teqeq	r1, #0
    126c:	96020000 	strls	r0, [r2], -r0
    1270:	01000005 	tsteq	r0, r5
    1274:	0000301f 	andeq	r3, r0, pc, lsl r0
    1278:	05040300 	streq	r0, [r4, #-768]	; 0xfffffd00
    127c:	00746e69 	rsbseq	r6, r4, r9, ror #28
    1280:	00056502 	andeq	r6, r5, r2, lsl #10
    1284:	30200100 	eorcc	r0, r0, r0, lsl #2
    1288:	04000000 	streq	r0, [r0], #-0
    128c:	00000571 	andeq	r0, r0, r1, ror r5
    1290:	81f42401 	mvnshi	r2, r1, lsl #8
    1294:	006c0000 	rsbeq	r0, ip, r0
    1298:	9c010000 	stcls	0, cr0, [r1], {-0}
    129c:	0000009b 	muleq	r0, fp, r0
    12a0:	00307205 	eorseq	r7, r0, r5, lsl #4
    12a4:	009b2401 	addseq	r2, fp, r1, lsl #8
    12a8:	91020000 	mrsls	r0, (UNDEF: 2)
    12ac:	3172056c 	cmncc	r2, ip, ror #10
    12b0:	9b240100 	blls	9016b8 <_stack+0x8816b8>
    12b4:	02000000 	andeq	r0, r0, #0
    12b8:	72056891 	andvc	r6, r5, #9502720	; 0x910000
    12bc:	24010032 	strcs	r0, [r1], #-50	; 0xffffffce
    12c0:	0000009b 	muleq	r0, fp, r0
    12c4:	06649102 	strbteq	r9, [r4], -r2, lsl #2
    12c8:	00737362 	rsbseq	r7, r3, r2, ror #6
    12cc:	00a22701 	adceq	r2, r2, r1, lsl #14
    12d0:	91020000 	mrsls	r0, (UNDEF: 2)
    12d4:	058e0774 	streq	r0, [lr, #1908]	; 0x774
    12d8:	28010000 	stmdacs	r1, {}	; <UNPREDICTABLE>
    12dc:	000000a2 	andeq	r0, r0, r2, lsr #1
    12e0:	00709102 	rsbseq	r9, r0, r2, lsl #2
    12e4:	55070408 	strpl	r0, [r7, #-1032]	; 0xfffffbf8
    12e8:	09000000 	stmdbeq	r0, {}	; <UNPREDICTABLE>
    12ec:	00003004 	andeq	r3, r0, r4
    12f0:	005f0000 	subseq	r0, pc, r0
    12f4:	00020000 	andeq	r0, r2, r0
    12f8:	00000440 	andeq	r0, r0, r0, asr #8
    12fc:	03800104 	orreq	r0, r0, #4, 2
    1300:	80000000 	andhi	r0, r0, r0
    1304:	800c0000 	andhi	r0, ip, r0
    1308:	72610000 	rsbvc	r0, r1, #0
    130c:	302d636d 	eorcc	r6, sp, sp, ror #6
    1310:	74732d39 	ldrbtvc	r2, [r3], #-3385	; 0xfffff2c7
    1314:	2e747261 	cdpcs	2, 7, cr7, cr4, cr1, {3}
    1318:	3a430053 	bcc	10c146c <_stack+0x104146c>
    131c:	7465625c 	strbtvc	r6, [r5], #-604	; 0xfffffda4
    1320:	35725c61 	ldrbcc	r5, [r2, #-3169]!	; 0xfffff39f
    1324:	4d5c352e 	cfldr64mi	mvdx3, [ip, #-184]	; 0xffffff48
    1328:	53696e69 	cmnpl	r9, #1680	; 0x690
    132c:	65747379 	ldrbvs	r7, [r4, #-889]!	; 0xfffffc87
    1330:	61525c6d 	cmpvs	r2, sp, ror #24
    1334:	65627073 	strbvs	r7, [r2, #-115]!	; 0xffffff8d
    1338:	50797272 	rsbspl	r7, r9, r2, ror r2
    133c:	72615c69 	rsbvc	r5, r1, #26880	; 0x6900
    1340:	78655f6d 	stmdavc	r5!, {r0, r2, r3, r5, r6, r8, r9, sl, fp, ip, lr}^
    1344:	554e4700 	strbpl	r4, [lr, #-1792]	; 0xfffff900
    1348:	20534120 	subscs	r4, r3, r0, lsr #2
    134c:	38322e32 	ldmdacc	r2!, {r1, r4, r5, r9, sl, fp, sp}
    1350:	0100302e 	tsteq	r0, lr, lsr #32
    1354:	Address 0x00001354 is out of bounds.


Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0xfffffeff
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10061201 	andne	r1, r6, r1, lsl #4
  10:	02000017 	andeq	r0, r0, #23
  14:	0b0b0024 	bleq	2c00ac <_stack+0x2400ac>
  18:	08030b3e 	stmdaeq	r3, {r1, r2, r3, r4, r5, r8, r9, fp}
  1c:	24030000 	strcs	r0, [r3], #-0
  20:	3e0b0b00 	vmlacc.f64	d0, d11, d0
  24:	000e030b 	andeq	r0, lr, fp, lsl #6
  28:	00350400 	eorseq	r0, r5, r0, lsl #8
  2c:	00001349 	andeq	r1, r0, r9, asr #6
  30:	03001605 	movweq	r1, #1541	; 0x605
  34:	3b0b3a0e 	blcc	2ce874 <_stack+0x24e874>
  38:	0013490b 	andseq	r4, r3, fp, lsl #18
  3c:	000f0600 	andeq	r0, pc, r0, lsl #12
  40:	13490b0b 	movtne	r0, #39691	; 0x9b0b
  44:	13070000 	movwne	r0, #28672	; 0x7000
  48:	3c0e0300 	stccc	3, cr0, [lr], {-0}
  4c:	08000019 	stmdaeq	r0, {r0, r3, r4}
  50:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
  54:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
  58:	00001349 	andeq	r1, r0, r9, asr #6
  5c:	0b011709 	bleq	45c88 <__bss_end__+0x3c838>
  60:	3b0b3a0b 	blcc	2ce894 <_stack+0x24e894>
  64:	0013010b 	andseq	r0, r3, fp, lsl #2
  68:	000d0a00 	andeq	r0, sp, r0, lsl #20
  6c:	0b3a0e03 	bleq	e83880 <_stack+0xe03880>
  70:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  74:	010b0000 	mrseq	r0, (UNDEF: 11)
  78:	01134901 	tsteq	r3, r1, lsl #18
  7c:	0c000013 	stceq	0, cr0, [r0], {19}
  80:	13490021 	movtne	r0, #36897	; 0x9021
  84:	00000b2f 	andeq	r0, r0, pc, lsr #22
  88:	0b01130d 	bleq	44cc4 <__bss_end__+0x3b874>
  8c:	3b0b3a0b 	blcc	2ce8c0 <_stack+0x24e8c0>
  90:	0013010b 	andseq	r0, r3, fp, lsl #2
  94:	000d0e00 	andeq	r0, sp, r0, lsl #28
  98:	0b3a0e03 	bleq	e838ac <_stack+0xe038ac>
  9c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  a0:	00000b38 	andeq	r0, r0, r8, lsr fp
  a4:	0b000f0f 	bleq	3ce8 <_start-0x4318>
  a8:	1000000b 	andne	r0, r0, fp
  ac:	13490026 	movtne	r0, #36902	; 0x9026
  b0:	13110000 	tstne	r1, #0
  b4:	0b0e0301 	bleq	380cc0 <_stack+0x300cc0>
  b8:	3b0b3a0b 	blcc	2ce8ec <_stack+0x24e8ec>
  bc:	0013010b 	andseq	r0, r3, fp, lsl #2
  c0:	000d1200 	andeq	r1, sp, r0, lsl #4
  c4:	0b3a0803 	bleq	e820d8 <_stack+0xe020d8>
  c8:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  cc:	00000b38 	andeq	r0, r0, r8, lsr fp
  d0:	03011313 	movweq	r1, #4883	; 0x1313
  d4:	3a050b0e 	bcc	142d14 <_stack+0xc2d14>
  d8:	010b3b0b 	tsteq	fp, fp, lsl #22
  dc:	14000013 	strne	r0, [r0], #-19	; 0xffffffed
  e0:	0e03000d 	cdpeq	0, 0, cr0, cr3, cr13, {0}
  e4:	0b3b0b3a 	bleq	ec2dd4 <_stack+0xe42dd4>
  e8:	05381349 	ldreq	r1, [r8, #-841]!	; 0xfffffcb7
  ec:	15150000 	ldrne	r0, [r5, #-0]
  f0:	00192700 	andseq	r2, r9, r0, lsl #14
  f4:	01151600 	tsteq	r5, r0, lsl #12
  f8:	13491927 	movtne	r1, #39207	; 0x9927
  fc:	00001301 	andeq	r1, r0, r1, lsl #6
 100:	49000517 	stmdbmi	r0, {r0, r1, r2, r4, r8, sl}
 104:	18000013 	stmdane	r0, {r0, r1, r4}
 108:	0e030113 	mcreq	1, 0, r0, cr3, cr3, {0}
 10c:	0b3a050b 	bleq	e81540 <_stack+0xe01540>
 110:	1301053b 	movwne	r0, #5435	; 0x153b
 114:	0d190000 	ldceq	0, cr0, [r9, #-0]
 118:	3a0e0300 	bcc	380d20 <_stack+0x300d20>
 11c:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 120:	000b3813 	andeq	r3, fp, r3, lsl r8
 124:	000d1a00 	andeq	r1, sp, r0, lsl #20
 128:	0b3a0e03 	bleq	e8393c <_stack+0xe0393c>
 12c:	1349053b 	movtne	r0, #38203	; 0x953b
 130:	00000538 	andeq	r0, r0, r8, lsr r5
 134:	0301131b 	movweq	r1, #4891	; 0x131b
 138:	3a0b0b0e 	bcc	2c2d78 <_stack+0x242d78>
 13c:	01053b0b 	tsteq	r5, fp, lsl #22
 140:	1c000013 	stcne	0, cr0, [r0], {19}
 144:	0b0b0113 	bleq	2c0598 <_stack+0x240598>
 148:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 14c:	00001301 	andeq	r1, r0, r1, lsl #6
 150:	0b01171d 	bleq	45dcc <__bss_end__+0x3c97c>
 154:	3b0b3a0b 	blcc	2ce988 <_stack+0x24e988>
 158:	00130105 	andseq	r0, r3, r5, lsl #2
 15c:	000d1e00 	andeq	r1, sp, r0, lsl #28
 160:	0b3a0e03 	bleq	e83974 <_stack+0xe03974>
 164:	1349053b 	movtne	r0, #38203	; 0x953b
 168:	151f0000 	ldrne	r0, [pc, #-0]	; 170 <_start-0x7e90>
 16c:	01192701 	tsteq	r9, r1, lsl #14
 170:	20000013 	andcs	r0, r0, r3, lsl r0
 174:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 178:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 17c:	193f1349 	ldmdbne	pc!, {r0, r3, r6, r8, r9, ip}	; <UNPREDICTABLE>
 180:	0000193c 	andeq	r1, r0, ip, lsr r9
 184:	03003421 	movweq	r3, #1057	; 0x421
 188:	3b0b3a0e 	blcc	2ce9c8 <_stack+0x24e9c8>
 18c:	3f13490b 	svccc	0x0013490b
 190:	00193c19 	andseq	r3, r9, r9, lsl ip
 194:	00342200 	eorseq	r2, r4, r0, lsl #4
 198:	0b3a0e03 	bleq	e839ac <_stack+0xe039ac>
 19c:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 1a0:	1802193f 	stmdane	r2, {r0, r1, r2, r3, r4, r5, r8, fp, ip}
 1a4:	2e230000 	cdpcs	0, 2, cr0, cr3, cr0, {0}
 1a8:	03193f01 	tsteq	r9, #1, 30
 1ac:	3b0b3a0e 	blcc	2ce9ec <_stack+0x24e9ec>
 1b0:	1119270b 	tstne	r9, fp, lsl #14
 1b4:	40061201 	andmi	r1, r6, r1, lsl #4
 1b8:	19429618 	stmdbne	r2, {r3, r4, r9, sl, ip, pc}^
 1bc:	00001301 	andeq	r1, r0, r1, lsl #6
 1c0:	03000524 	movweq	r0, #1316	; 0x524
 1c4:	3b0b3a08 	blcc	2ce9ec <_stack+0x24e9ec>
 1c8:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
 1cc:	25000018 	strcs	r0, [r0, #-24]	; 0xffffffe8
 1d0:	0e030005 	cdpeq	0, 0, cr0, cr3, cr5, {0}
 1d4:	0b3b0b3a 	bleq	ec2ec4 <_stack+0xe42ec4>
 1d8:	18021349 	stmdane	r2, {r0, r3, r6, r8, r9, ip}
 1dc:	34260000 	strtcc	r0, [r6], #-0
 1e0:	3a0e0300 	bcc	380de8 <_stack+0x300de8>
 1e4:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 1e8:	00180213 	andseq	r0, r8, r3, lsl r2
 1ec:	11010000 	mrsne	r0, (UNDEF: 1)
 1f0:	130e2501 	movwne	r2, #58625	; 0xe501
 1f4:	1b0e030b 	blne	380e28 <_stack+0x300e28>
 1f8:	1201110e 	andne	r1, r1, #-2147483645	; 0x80000003
 1fc:	00171006 	andseq	r1, r7, r6
 200:	00240200 	eoreq	r0, r4, r0, lsl #4
 204:	0b3e0b0b 	bleq	f82e38 <_stack+0xf02e38>
 208:	00000e03 	andeq	r0, r0, r3, lsl #28
 20c:	0b002403 	bleq	9220 <impure_data+0x258>
 210:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
 214:	04000008 	streq	r0, [r0], #-8
 218:	0e030016 	mcreq	0, 0, r0, cr3, cr6, {0}
 21c:	0b3b0b3a 	bleq	ec2f0c <_stack+0xe42f0c>
 220:	00001349 	andeq	r1, r0, r9, asr #6
 224:	0b000f05 	bleq	3e40 <_start-0x41c0>
 228:	0013490b 	andseq	r4, r3, fp, lsl #18
 22c:	00130600 	andseq	r0, r3, r0, lsl #12
 230:	193c0e03 	ldmdbne	ip!, {r0, r1, r9, sl, fp}
 234:	16070000 	strne	r0, [r7], -r0
 238:	3a0e0300 	bcc	380e40 <_stack+0x300e40>
 23c:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 240:	08000013 	stmdaeq	r0, {r0, r1, r4}
 244:	0b0b0117 	bleq	2c06a8 <_stack+0x2406a8>
 248:	0b3b0b3a 	bleq	ec2f38 <_stack+0xe42f38>
 24c:	00001301 	andeq	r1, r0, r1, lsl #6
 250:	03000d09 	movweq	r0, #3337	; 0xd09
 254:	3b0b3a0e 	blcc	2cea94 <_stack+0x24ea94>
 258:	0013490b 	andseq	r4, r3, fp, lsl #18
 25c:	01010a00 	tsteq	r1, r0, lsl #20
 260:	13011349 	movwne	r1, #4937	; 0x1349
 264:	210b0000 	mrscs	r0, (UNDEF: 11)
 268:	2f134900 	svccs	0x00134900
 26c:	0c00000b 	stceq	0, cr0, [r0], {11}
 270:	0b0b0113 	bleq	2c06c4 <_stack+0x2406c4>
 274:	0b3b0b3a 	bleq	ec2f64 <_stack+0xe42f64>
 278:	00001301 	andeq	r1, r0, r1, lsl #6
 27c:	03000d0d 	movweq	r0, #3341	; 0xd0d
 280:	3b0b3a0e 	blcc	2ceac0 <_stack+0x24eac0>
 284:	3813490b 	ldmdacc	r3, {r0, r1, r3, r8, fp, lr}
 288:	0e00000b 	cdpeq	0, 0, cr0, cr0, cr11, {0}
 28c:	0b0b000f 	bleq	2c02d0 <_stack+0x2402d0>
 290:	130f0000 	movwne	r0, #61440	; 0xf000
 294:	0b0e0301 	bleq	380ea0 <_stack+0x300ea0>
 298:	3b0b3a0b 	blcc	2ceacc <_stack+0x24eacc>
 29c:	0013010b 	andseq	r0, r3, fp, lsl #2
 2a0:	000d1000 	andeq	r1, sp, r0
 2a4:	0b3a0803 	bleq	e822b8 <_stack+0xe022b8>
 2a8:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 2ac:	00000b38 	andeq	r0, r0, r8, lsr fp
 2b0:	03011311 	movweq	r1, #4881	; 0x1311
 2b4:	3a050b0e 	bcc	142ef4 <_stack+0xc2ef4>
 2b8:	010b3b0b 	tsteq	fp, fp, lsl #22
 2bc:	12000013 	andne	r0, r0, #19
 2c0:	0e03000d 	cdpeq	0, 0, cr0, cr3, cr13, {0}
 2c4:	0b3b0b3a 	bleq	ec2fb4 <_stack+0xe42fb4>
 2c8:	05381349 	ldreq	r1, [r8, #-841]!	; 0xfffffcb7
 2cc:	15130000 	ldrne	r0, [r3, #-0]
 2d0:	00192700 	andseq	r2, r9, r0, lsl #14
 2d4:	01151400 	tsteq	r5, r0, lsl #8
 2d8:	13491927 	movtne	r1, #39207	; 0x9927
 2dc:	00001301 	andeq	r1, r0, r1, lsl #6
 2e0:	49000515 	stmdbmi	r0, {r0, r2, r4, r8, sl}
 2e4:	16000013 			; <UNDEFINED> instruction: 0x16000013
 2e8:	13490026 	movtne	r0, #36902	; 0x9026
 2ec:	13170000 	tstne	r7, #0
 2f0:	0b0e0301 	bleq	380efc <_stack+0x300efc>
 2f4:	3b0b3a05 	blcc	2ceb10 <_stack+0x24eb10>
 2f8:	00130105 	andseq	r0, r3, r5, lsl #2
 2fc:	000d1800 	andeq	r1, sp, r0, lsl #16
 300:	0b3a0e03 	bleq	e83b14 <_stack+0xe03b14>
 304:	1349053b 	movtne	r0, #38203	; 0x953b
 308:	00000b38 	andeq	r0, r0, r8, lsr fp
 30c:	03000d19 	movweq	r0, #3353	; 0xd19
 310:	3b0b3a0e 	blcc	2ceb50 <_stack+0x24eb50>
 314:	38134905 	ldmdacc	r3, {r0, r2, r8, fp, lr}
 318:	1a000005 	bne	334 <_start-0x7ccc>
 31c:	0e030113 	mcreq	1, 0, r0, cr3, cr3, {0}
 320:	0b3a0b0b 	bleq	e82f54 <_stack+0xe02f54>
 324:	1301053b 	movwne	r0, #5435	; 0x153b
 328:	131b0000 	tstne	fp, #0
 32c:	3a0b0b01 	bcc	2c2f38 <_stack+0x242f38>
 330:	01053b0b 	tsteq	r5, fp, lsl #22
 334:	1c000013 	stcne	0, cr0, [r0], {19}
 338:	0b0b0117 	bleq	2c079c <_stack+0x24079c>
 33c:	053b0b3a 	ldreq	r0, [fp, #-2874]!	; 0xfffff4c6
 340:	00001301 	andeq	r1, r0, r1, lsl #6
 344:	03000d1d 	movweq	r0, #3357	; 0xd1d
 348:	3b0b3a0e 	blcc	2ceb88 <_stack+0x24eb88>
 34c:	00134905 	andseq	r4, r3, r5, lsl #18
 350:	01151e00 	tsteq	r5, r0, lsl #28
 354:	13011927 	movwne	r1, #6439	; 0x1927
 358:	341f0000 	ldrcc	r0, [pc], #-0	; 360 <_start-0x7ca0>
 35c:	3a0e0300 	bcc	380f64 <_stack+0x300f64>
 360:	49053b0b 	stmdbmi	r5, {r0, r1, r3, r8, r9, fp, ip, sp}
 364:	3c193f13 	ldccc	15, cr3, [r9], {19}
 368:	20000019 	andcs	r0, r0, r9, lsl r0
 36c:	0e030034 	mcreq	0, 0, r0, cr3, cr4, {1}
 370:	0b3b0b3a 	bleq	ec3060 <_stack+0xe43060>
 374:	193f1349 	ldmdbne	pc!, {r0, r3, r6, r8, r9, ip}	; <UNPREDICTABLE>
 378:	0000193c 	andeq	r1, r0, ip, lsr r9
 37c:	3f012e21 	svccc	0x00012e21
 380:	3a0e0319 	bcc	380fec <_stack+0x300fec>
 384:	270b3b0b 	strcs	r3, [fp, -fp, lsl #22]
 388:	11134919 	tstne	r3, r9, lsl r9
 38c:	40061201 	andmi	r1, r6, r1, lsl #4
 390:	19429718 	stmdbne	r2, {r3, r4, r8, r9, sl, ip, pc}^
 394:	05220000 	streq	r0, [r2, #-0]!
 398:	3a0e0300 	bcc	380fa0 <_stack+0x300fa0>
 39c:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 3a0:	00180213 	andseq	r0, r8, r3, lsl r2
 3a4:	00342300 	eorseq	r2, r4, r0, lsl #6
 3a8:	0b3a0e03 	bleq	e83bbc <_stack+0xe03bbc>
 3ac:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 3b0:	00001802 	andeq	r1, r0, r2, lsl #16
 3b4:	01110100 	tsteq	r1, r0, lsl #2
 3b8:	0b130e25 	bleq	4c3c54 <_stack+0x443c54>
 3bc:	0e1b0e03 	cdpeq	14, 1, cr0, cr11, cr3, {0}
 3c0:	06120111 			; <UNDEFINED> instruction: 0x06120111
 3c4:	00001710 	andeq	r1, r0, r0, lsl r7
 3c8:	03003402 	movweq	r3, #1026	; 0x402
 3cc:	3b0b3a0e 	blcc	2cec0c <_stack+0x24ec0c>
 3d0:	3f13490b 	svccc	0x0013490b
 3d4:	00193c19 	andseq	r3, r9, r9, lsl ip
 3d8:	00240300 	eoreq	r0, r4, r0, lsl #6
 3dc:	0b3e0b0b 	bleq	f83010 <_stack+0xf03010>
 3e0:	00000803 	andeq	r0, r0, r3, lsl #16
 3e4:	3f012e04 	svccc	0x00012e04
 3e8:	3a0e0319 	bcc	381054 <_stack+0x301054>
 3ec:	270b3b0b 	strcs	r3, [fp, -fp, lsl #22]
 3f0:	12011119 	andne	r1, r1, #1073741830	; 0x40000006
 3f4:	96184006 	ldrls	r4, [r8], -r6
 3f8:	13011942 	movwne	r1, #6466	; 0x1942
 3fc:	05050000 	streq	r0, [r5, #-0]
 400:	3a080300 	bcc	201008 <_stack+0x181008>
 404:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
 408:	00180213 	andseq	r0, r8, r3, lsl r2
 40c:	00340600 	eorseq	r0, r4, r0, lsl #12
 410:	0b3a0803 	bleq	e82424 <_stack+0xe02424>
 414:	13490b3b 	movtne	r0, #39739	; 0x9b3b
 418:	00001802 	andeq	r1, r0, r2, lsl #16
 41c:	03003407 	movweq	r3, #1031	; 0x407
 420:	3b0b3a0e 	blcc	2cec60 <_stack+0x24ec60>
 424:	0213490b 	andseq	r4, r3, #180224	; 0x2c000
 428:	08000018 	stmdaeq	r0, {r3, r4}
 42c:	0b0b0024 	bleq	2c04c4 <_stack+0x2404c4>
 430:	0e030b3e 	vmoveq.16	d3[0], r0
 434:	0f090000 	svceq	0x00090000
 438:	490b0b00 	stmdbmi	fp, {r8, r9, fp}
 43c:	00000013 	andeq	r0, r0, r3, lsl r0
 440:	10001101 	andne	r1, r0, r1, lsl #2
 444:	12011106 	andne	r1, r1, #-2147483647	; 0x80000001
 448:	1b080301 	blne	201054 <_stack+0x181054>
 44c:	13082508 	movwne	r2, #34056	; 0x8508
 450:	00000005 	andeq	r0, r0, r5

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	000001a6 	andeq	r0, r0, r6, lsr #3
   4:	01570002 	cmpeq	r7, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	63010000 	movwvs	r0, #4096	; 0x1000
  1c:	72705c3a 	rsbsvc	r5, r0, #14848	; 0x3a00
  20:	6172676f 	cmnvs	r2, pc, ror #14
  24:	6966206d 	stmdbvs	r6!, {r0, r2, r3, r5, r6, sp}^
  28:	5c73656c 	cfldr64pl	mvdx6, [r3], #-432	; 0xfffffe50
  2c:	20756e67 	rsbscs	r6, r5, r7, ror #28
  30:	6c6f6f74 	stclvs	15, cr6, [pc], #-464	; fffffe68 <_stack+0xfff7fe68>
  34:	72612073 	rsbvc	r2, r1, #115	; 0x73
  38:	6d65206d 	stclvs	0, cr2, [r5, #-436]!	; 0xfffffe4c
  3c:	64646562 	strbtvs	r6, [r4], #-1378	; 0xfffffa9e
  40:	365c6465 	ldrbcc	r6, [ip], -r5, ror #8
  44:	31303220 	teqcc	r0, r0, lsr #4
  48:	32712d37 	rsbscc	r2, r1, #3520	; 0xdc0
  4c:	6470752d 	ldrbtvs	r7, [r0], #-1325	; 0xfffffad3
  50:	5c657461 	cfstrdpl	mvd7, [r5], #-388	; 0xfffffe7c
  54:	2d6d7261 	sfmcs	f7, 2, [sp, #-388]!	; 0xfffffe7c
  58:	656e6f6e 	strbvs	r6, [lr, #-3950]!	; 0xfffff092
  5c:	6261652d 	rsbvs	r6, r1, #188743680	; 0xb400000
  60:	6e695c69 	cdpvs	12, 6, cr5, cr9, cr9, {3}
  64:	64756c63 	ldrbtvs	r6, [r5], #-3171	; 0xfffff39d
  68:	79735c65 	ldmdbvc	r3!, {r0, r2, r5, r6, sl, fp, ip, lr}^
  6c:	3a630073 	bcc	18c0240 <_stack+0x1840240>
  70:	6f72705c 	svcvs	0x0072705c
  74:	6d617267 	sfmvs	f7, 2, [r1, #-412]!	; 0xfffffe64
  78:	6c696620 	stclvs	6, cr6, [r9], #-128	; 0xffffff80
  7c:	675c7365 	ldrbvs	r7, [ip, -r5, ror #6]
  80:	7420756e 	strtvc	r7, [r0], #-1390	; 0xfffffa92
  84:	736c6f6f 	cmnvc	ip, #444	; 0x1bc
  88:	6d726120 	ldfvse	f6, [r2, #-128]!	; 0xffffff80
  8c:	626d6520 	rsbvs	r6, sp, #32, 10	; 0x8000000
  90:	65646465 	strbvs	r6, [r4, #-1125]!	; 0xfffffb9b
  94:	20365c64 	eorscs	r5, r6, r4, ror #24
  98:	37313032 			; <UNDEFINED> instruction: 0x37313032
  9c:	2d32712d 	ldfcss	f7, [r2, #-180]!	; 0xffffff4c
  a0:	61647075 	smcvs	18181	; 0x4705
  a4:	6c5c6574 	cfldr64vs	mvdx6, [ip], {116}	; 0x74
  a8:	675c6269 	ldrbvs	r6, [ip, -r9, ror #4]
  ac:	615c6363 	cmpvs	ip, r3, ror #6
  b0:	6e2d6d72 	mcrvs	13, 1, r6, cr13, cr2, {3}
  b4:	2d656e6f 	stclcs	14, cr6, [r5, #-444]!	; 0xfffffe44
  b8:	69626165 	stmdbvs	r2!, {r0, r2, r5, r6, r8, sp, lr}^
  bc:	332e365c 			; <UNDEFINED> instruction: 0x332e365c
  c0:	695c312e 	ldmdbvs	ip, {r1, r2, r3, r5, r8, ip, sp}^
  c4:	756c636e 	strbvc	r6, [ip, #-878]!	; 0xfffffc92
  c8:	63006564 	movwvs	r6, #1380	; 0x564
  cc:	72705c3a 	rsbsvc	r5, r0, #14848	; 0x3a00
  d0:	6172676f 	cmnvs	r2, pc, ror #14
  d4:	6966206d 	stmdbvs	r6!, {r0, r2, r3, r5, r6, sp}^
  d8:	5c73656c 	cfldr64pl	mvdx6, [r3], #-432	; 0xfffffe50
  dc:	20756e67 	rsbscs	r6, r5, r7, ror #28
  e0:	6c6f6f74 	stclvs	15, cr6, [pc], #-464	; ffffff18 <_stack+0xfff7ff18>
  e4:	72612073 	rsbvc	r2, r1, #115	; 0x73
  e8:	6d65206d 	stclvs	0, cr2, [r5, #-436]!	; 0xfffffe4c
  ec:	64646562 	strbtvs	r6, [r4], #-1378	; 0xfffffa9e
  f0:	365c6465 	ldrbcc	r6, [ip], -r5, ror #8
  f4:	31303220 	teqcc	r0, r0, lsr #4
  f8:	32712d37 	rsbscc	r2, r1, #3520	; 0xdc0
  fc:	6470752d 	ldrbtvs	r7, [r0], #-1325	; 0xfffffad3
 100:	5c657461 	cfstrdpl	mvd7, [r5], #-388	; 0xfffffe7c
 104:	2d6d7261 	sfmcs	f7, 2, [sp, #-388]!	; 0xfffffe7c
 108:	656e6f6e 	strbvs	r6, [lr, #-3950]!	; 0xfffff092
 10c:	6261652d 	rsbvs	r6, r1, #188743680	; 0xb400000
 110:	6e695c69 	cdpvs	12, 6, cr5, cr9, cr9, {3}
 114:	64756c63 	ldrbtvs	r6, [r5], #-3171	; 0xfffff39d
 118:	61000065 	tstvs	r0, r5, rrx
 11c:	652d6d72 	strvs	r6, [sp, #-3442]!	; 0xfffff28e
 120:	00632e78 	rsbeq	r2, r3, r8, ror lr
 124:	6c000000 	stcvs	0, cr0, [r0], {-0}
 128:	2e6b636f 	cdpcs	3, 6, cr6, cr11, cr15, {3}
 12c:	00010068 	andeq	r0, r1, r8, rrx
 130:	79745f00 	ldmdbvc	r4!, {r8, r9, sl, fp, ip, lr}^
 134:	2e736570 	mrccs	5, 3, r6, cr3, cr0, {3}
 138:	00010068 	andeq	r0, r1, r8, rrx
 13c:	64747300 	ldrbtvs	r7, [r4], #-768	; 0xfffffd00
 140:	2e666564 	cdpcs	5, 6, cr6, cr6, cr4, {3}
 144:	00020068 	andeq	r0, r2, r8, rrx
 148:	65657200 	strbvs	r7, [r5, #-512]!	; 0xfffffe00
 14c:	682e746e 	stmdavs	lr!, {r1, r2, r3, r5, r6, sl, ip, sp, lr}
 150:	00000100 	andeq	r0, r0, r0, lsl #2
 154:	6c647473 	cfstrdvs	mvd7, [r4], #-460	; 0xfffffe34
 158:	682e6269 	stmdavs	lr!, {r0, r3, r5, r6, r9, sp, lr}
 15c:	00000300 	andeq	r0, r0, r0, lsl #6
 160:	02050000 	andeq	r0, r5, #0
 164:	0000800c 	andeq	r8, r0, ip
 168:	bf010a03 	svclt	0x00010a03
 16c:	00855b08 	addeq	r5, r5, r8, lsl #22
 170:	67010402 	strvs	r0, [r1, -r2, lsl #8]
 174:	040200d8 	streq	r0, [r2], #-216	; 0xffffff28
 178:	02006703 	andeq	r6, r0, #786432	; 0xc0000
 17c:	00b90304 	adcseq	r0, r9, r4, lsl #6
 180:	06010402 	streq	r0, [r1], -r2, lsl #8
 184:	bc6d0666 	stcllt	6, cr0, [sp], #-408	; 0xfffffe68
 188:	03040200 	movweq	r0, #16896	; 0x4200
 18c:	02008206 	andeq	r8, r0, #1610612736	; 0x60000000
 190:	069e0104 	ldreq	r0, [lr], r4, lsl #2
 194:	0200bcbe 	andeq	fp, r0, #48640	; 0xbe00
 198:	9e060304 	cdpls	3, 0, cr0, cr6, cr4, {0}
 19c:	01040200 	mrseq	r0, R12_usr
 1a0:	7803069e 	stmdavc	r3, {r1, r2, r3, r4, r7, r9, sl}
 1a4:	000202d6 	ldrdeq	r0, [r2], -r6
 1a8:	01830101 	orreq	r0, r3, r1, lsl #2
 1ac:	00020000 	andeq	r0, r2, r0
 1b0:	00000168 	andeq	r0, r0, r8, ror #2
 1b4:	0efb0102 	cdpeq	1, 15, cr0, cr11, cr2, {0}
 1b8:	0101000d 	tsteq	r1, sp
 1bc:	00000101 	andeq	r0, r0, r1, lsl #2
 1c0:	00000100 	andeq	r0, r0, r0, lsl #2
 1c4:	5c3a6301 	ldcpl	3, cr6, [sl], #-4
 1c8:	676f7270 			; <UNDEFINED> instruction: 0x676f7270
 1cc:	206d6172 	rsbcs	r6, sp, r2, ror r1
 1d0:	656c6966 	strbvs	r6, [ip, #-2406]!	; 0xfffff69a
 1d4:	6e675c73 	mcrvs	12, 3, r5, cr7, cr3, {3}
 1d8:	6f742075 	svcvs	0x00742075
 1dc:	20736c6f 	rsbscs	r6, r3, pc, ror #24
 1e0:	206d7261 	rsbcs	r7, sp, r1, ror #4
 1e4:	65626d65 	strbvs	r6, [r2, #-3429]!	; 0xfffff29b
 1e8:	64656464 	strbtvs	r6, [r5], #-1124	; 0xfffffb9c
 1ec:	3220365c 	eorcc	r3, r0, #92, 12	; 0x5c00000
 1f0:	2d373130 	ldfcss	f3, [r7, #-192]!	; 0xffffff40
 1f4:	752d3271 	strvc	r3, [sp, #-625]!	; 0xfffffd8f
 1f8:	74616470 	strbtvc	r6, [r1], #-1136	; 0xfffffb90
 1fc:	72615c65 	rsbvc	r5, r1, #25856	; 0x6500
 200:	6f6e2d6d 	svcvs	0x006e2d6d
 204:	652d656e 	strvs	r6, [sp, #-1390]!	; 0xfffffa92
 208:	5c696261 	sfmpl	f6, 2, [r9], #-388	; 0xfffffe7c
 20c:	6c636e69 	stclvs	14, cr6, [r3], #-420	; 0xfffffe5c
 210:	5c656475 	cfstrdpl	mvd6, [r5], #-468	; 0xfffffe2c
 214:	00737973 	rsbseq	r7, r3, r3, ror r9
 218:	705c3a63 	subsvc	r3, ip, r3, ror #20
 21c:	72676f72 	rsbvc	r6, r7, #456	; 0x1c8
 220:	66206d61 	strtvs	r6, [r0], -r1, ror #26
 224:	73656c69 	cmnvc	r5, #26880	; 0x6900
 228:	756e675c 	strbvc	r6, [lr, #-1884]!	; 0xfffff8a4
 22c:	6f6f7420 	svcvs	0x006f7420
 230:	6120736c 			; <UNDEFINED> instruction: 0x6120736c
 234:	65206d72 	strvs	r6, [r0, #-3442]!	; 0xfffff28e
 238:	6465626d 	strbtvs	r6, [r5], #-621	; 0xfffffd93
 23c:	5c646564 	cfstr64pl	mvdx6, [r4], #-400	; 0xfffffe70
 240:	30322036 	eorscc	r2, r2, r6, lsr r0
 244:	712d3731 			; <UNDEFINED> instruction: 0x712d3731
 248:	70752d32 	rsbsvc	r2, r5, r2, lsr sp
 24c:	65746164 	ldrbvs	r6, [r4, #-356]!	; 0xfffffe9c
 250:	62696c5c 	rsbvs	r6, r9, #92, 24	; 0x5c00
 254:	6363675c 	cmnvs	r3, #92, 14	; 0x1700000
 258:	6d72615c 	ldfvse	f6, [r2, #-368]!	; 0xfffffe90
 25c:	6e6f6e2d 	cdpvs	14, 6, cr6, cr15, cr13, {1}
 260:	61652d65 	cmnvs	r5, r5, ror #26
 264:	365c6962 	ldrbcc	r6, [ip], -r2, ror #18
 268:	312e332e 			; <UNDEFINED> instruction: 0x312e332e
 26c:	636e695c 	cmnvs	lr, #92, 18	; 0x170000
 270:	6564756c 	strbvs	r7, [r4, #-1388]!	; 0xfffffa94
 274:	5c3a6300 	ldcpl	3, cr6, [sl], #-0
 278:	676f7270 			; <UNDEFINED> instruction: 0x676f7270
 27c:	206d6172 	rsbcs	r6, sp, r2, ror r1
 280:	656c6966 	strbvs	r6, [ip, #-2406]!	; 0xfffff69a
 284:	6e675c73 	mcrvs	12, 3, r5, cr7, cr3, {3}
 288:	6f742075 	svcvs	0x00742075
 28c:	20736c6f 	rsbscs	r6, r3, pc, ror #24
 290:	206d7261 	rsbcs	r7, sp, r1, ror #4
 294:	65626d65 	strbvs	r6, [r2, #-3429]!	; 0xfffff29b
 298:	64656464 	strbtvs	r6, [r5], #-1124	; 0xfffffb9c
 29c:	3220365c 	eorcc	r3, r0, #92, 12	; 0x5c00000
 2a0:	2d373130 	ldfcss	f3, [r7, #-192]!	; 0xffffff40
 2a4:	752d3271 	strvc	r3, [sp, #-625]!	; 0xfffffd8f
 2a8:	74616470 	strbtvc	r6, [r1], #-1136	; 0xfffffb90
 2ac:	72615c65 	rsbvc	r5, r1, #25856	; 0x6500
 2b0:	6f6e2d6d 	svcvs	0x006e2d6d
 2b4:	652d656e 	strvs	r6, [sp, #-1390]!	; 0xfffffa92
 2b8:	5c696261 	sfmpl	f6, 2, [r9], #-388	; 0xfffffe7c
 2bc:	6c636e69 	stclvs	14, cr6, [r3], #-420	; 0xfffffe5c
 2c0:	00656475 	rsbeq	r6, r5, r5, ror r4
 2c4:	6d726100 	ldfvse	f6, [r2, #-0]
 2c8:	39302d63 	ldmdbcc	r0!, {r0, r1, r5, r6, r8, sl, fp, sp}
 2cc:	7473632d 	ldrbtvc	r6, [r3], #-813	; 0xfffffcd3
 2d0:	2e736275 	mrccs	2, 3, r6, cr3, cr5, {3}
 2d4:	00000063 	andeq	r0, r0, r3, rrx
 2d8:	636f6c00 	cmnvs	pc, #0, 24
 2dc:	00682e6b 	rsbeq	r2, r8, fp, ror #28
 2e0:	5f000001 	svcpl	0x00000001
 2e4:	65707974 	ldrbvs	r7, [r0, #-2420]!	; 0xfffff68c
 2e8:	00682e73 	rsbeq	r2, r8, r3, ror lr
 2ec:	73000001 	movwvc	r0, #1
 2f0:	65646474 	strbvs	r6, [r4, #-1140]!	; 0xfffffb8c
 2f4:	00682e66 	rsbeq	r2, r8, r6, ror #28
 2f8:	72000002 	andvc	r0, r0, #2
 2fc:	746e6565 	strbtvc	r6, [lr], #-1381	; 0xfffffa9b
 300:	0100682e 	tsteq	r0, lr, lsr #16
 304:	79740000 	ldmdbvc	r4!, {}^	; <UNPREDICTABLE>
 308:	2e736570 	mrccs	5, 3, r6, cr3, cr0, {3}
 30c:	00010068 	andeq	r0, r1, r8, rrx
 310:	6d697400 	cfstrdvs	mvd7, [r9, #-0]
 314:	00682e65 	rsbeq	r2, r8, r5, ror #28
 318:	00000003 	andeq	r0, r0, r3
 31c:	78020500 	stmdavc	r2, {r8, sl}
 320:	03000081 	movweq	r0, #129	; 0x81
 324:	9f87013f 	svcls	0x0087013f
 328:	2ff384a0 	svccs	0x00f384a0
 32c:	01000802 	tsteq	r0, r2, lsl #16
 330:	00004b01 	andeq	r4, r0, r1, lsl #22
 334:	29000200 	stmdbcs	r0, {r9}
 338:	02000000 	andeq	r0, r0, #0
 33c:	0d0efb01 	vstreq	d15, [lr, #-4]
 340:	01010100 	mrseq	r0, (UNDEF: 17)
 344:	00000001 	andeq	r0, r0, r1
 348:	01000001 	tsteq	r0, r1
 34c:	6d726100 	ldfvse	f6, [r2, #-0]
 350:	39302d63 	ldmdbcc	r0!, {r0, r1, r5, r6, r8, sl, fp, sp}
 354:	7473632d 	ldrbtvc	r6, [r3], #-813	; 0xfffffcd3
 358:	75747261 	ldrbvc	r7, [r4, #-609]!	; 0xfffffd9f
 35c:	00632e70 	rsbeq	r2, r3, r0, ror lr
 360:	00000000 	andeq	r0, r0, r0
 364:	f4020500 	vst3.8	{d0,d2,d4}, [r2], r0
 368:	03000081 	movweq	r0, #129	; 0x81
 36c:	67bc0124 	ldrvs	r0, [ip, r4, lsr #2]!
 370:	2f660b03 	svccs	0x00660b03
 374:	0200869d 	andeq	r8, r0, #164626432	; 0x9d00000
 378:	02850104 	addeq	r0, r5, #4, 2
 37c:	01010002 	tsteq	r1, r2
 380:	0000003d 	andeq	r0, r0, sp, lsr r0
 384:	00260002 	eoreq	r0, r6, r2
 388:	01020000 	mrseq	r0, (UNDEF: 2)
 38c:	000d0efb 	strdeq	r0, [sp], -fp
 390:	01010101 	tsteq	r1, r1, lsl #2
 394:	01000000 	mrseq	r0, (UNDEF: 0)
 398:	00010000 	andeq	r0, r1, r0
 39c:	636d7261 	cmnvs	sp, #268435462	; 0x10000006
 3a0:	2d39302d 	ldccs	0, cr3, [r9, #-180]!	; 0xffffff4c
 3a4:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
 3a8:	00532e74 	subseq	r2, r3, r4, ror lr
 3ac:	00000000 	andeq	r0, r0, r0
 3b0:	00020500 	andeq	r0, r2, r0, lsl #10
 3b4:	03000080 	movweq	r0, #128	; 0x80
 3b8:	31310126 	teqcc	r1, r6, lsr #2
 3bc:	01000202 	tsteq	r0, r2, lsl #4
 3c0:	Address 0x000003c0 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	00000018 	andeq	r0, r0, r8, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	0000800c 	andeq	r8, r0, ip
  1c:	0000016c 	andeq	r0, r0, ip, ror #2
  20:	8b080e42 	blhi	203930 <_stack+0x183930>
  24:	42018e02 	andmi	r8, r1, #2, 28
  28:	00040b0c 	andeq	r0, r4, ip, lsl #22
  2c:	0000000c 	andeq	r0, r0, ip
  30:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  34:	7c020001 	stcvc	0, cr0, [r2], {1}
  38:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  3c:	0000001c 	andeq	r0, r0, ip, lsl r0
  40:	0000002c 	andeq	r0, r0, ip, lsr #32
  44:	00008178 	andeq	r8, r0, r8, ror r1
  48:	0000007c 	andeq	r0, r0, ip, ror r0
  4c:	8b040e42 	blhi	10395c <_stack+0x8395c>
  50:	0b0d4201 	bleq	35085c <_stack+0x2d085c>
  54:	420d0d76 	andmi	r0, sp, #7552	; 0x1d80
  58:	00000ecb 	andeq	r0, r0, fp, asr #29
  5c:	0000000c 	andeq	r0, r0, ip
  60:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  64:	7c020001 	stcvc	0, cr0, [r2], {1}
  68:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  6c:	00000018 	andeq	r0, r0, r8, lsl r0
  70:	0000005c 	andeq	r0, r0, ip, asr r0
  74:	000081f4 	strdeq	r8, [r0], -r4
  78:	0000006c 	andeq	r0, r0, ip, rrx
  7c:	8b080e42 	blhi	20398c <_stack+0x18398c>
  80:	42018e02 	andmi	r8, r1, #2, 28
  84:	00040b0c 	andeq	r0, r4, ip, lsl #22
  88:	0000000c 	andeq	r0, r0, ip
  8c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  90:	7c020001 	stcvc	0, cr0, [r2], {1}
  94:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  98:	0000000c 	andeq	r0, r0, ip
  9c:	00000088 	andeq	r0, r0, r8, lsl #1
  a0:	00008260 	andeq	r8, r0, r0, ror #4
  a4:	00000010 	andeq	r0, r0, r0, lsl r0
  a8:	0000000c 	andeq	r0, r0, ip
  ac:	00000088 	andeq	r0, r0, r8, lsl #1
  b0:	00008270 	andeq	r8, r0, r0, ror r2
  b4:	00000010 	andeq	r0, r0, r0, lsl r0
  b8:	0000000c 	andeq	r0, r0, ip
  bc:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  c0:	7c020001 	stcvc	0, cr0, [r2], {1}
  c4:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  c8:	00000044 	andeq	r0, r0, r4, asr #32
  cc:	000000b8 	strheq	r0, [r0], -r8
  d0:	00008280 	andeq	r8, r0, r0, lsl #5
  d4:	0000058c 	andeq	r0, r0, ip, lsl #11
  d8:	84240e42 	strthi	r0, [r4], #-3650	; 0xfffff1be
  dc:	86088509 	strhi	r8, [r8], -r9, lsl #10
  e0:	88068707 	stmdahi	r6, {r0, r1, r2, r8, r9, sl, pc}
  e4:	8a048905 	bhi	122500 <_stack+0xa2500>
  e8:	8e028b03 	vmlahi.f64	d8, d2, d3
  ec:	300e4401 	andcc	r4, lr, r1, lsl #8
  f0:	0e0acf02 	cdpeq	15, 0, cr12, cr10, cr2, {0}
  f4:	450b4224 	strmi	r4, [fp, #-548]	; 0xfffffddc
  f8:	42240e0a 	eormi	r0, r4, #10, 28	; 0xa0
  fc:	0e0a560b 	cfmadd32eq	mvax0, mvfx5, mvfx10, mvfx11
 100:	4c0b4224 	sfmmi	f4, 4, [fp], {36}	; 0x24
 104:	42240e0a 	eormi	r0, r4, #10, 28	; 0xa0
 108:	0a5a020b 	beq	168093c <_stack+0x160093c>
 10c:	0b42240e 	bleq	108914c <_stack+0x100914c>
 110:	0000000c 	andeq	r0, r0, ip
 114:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 118:	7c020001 	stcvc	0, cr0, [r2], {1}
 11c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 120:	0000000c 	andeq	r0, r0, ip
 124:	00000110 	andeq	r0, r0, r0, lsl r1
 128:	0000880c 	andeq	r8, r0, ip, lsl #16
 12c:	0000000c 	andeq	r0, r0, ip
 130:	0000000c 	andeq	r0, r0, ip
 134:	00000110 	andeq	r0, r0, r0, lsl r1
 138:	00008818 	andeq	r8, r0, r8, lsl r8
 13c:	0000000c 	andeq	r0, r0, ip
 140:	0000000c 	andeq	r0, r0, ip
 144:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 148:	7c020001 	stcvc	0, cr0, [r2], {1}
 14c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 150:	00000018 	andeq	r0, r0, r8, lsl r0
 154:	00000140 	andeq	r0, r0, r0, asr #2
 158:	00008824 	andeq	r8, r0, r4, lsr #16
 15c:	00000026 	andeq	r0, r0, r6, lsr #32
 160:	83100e41 	tsthi	r0, #1040	; 0x410
 164:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 168:	00018e02 	andeq	r8, r1, r2, lsl #28
 16c:	0000000c 	andeq	r0, r0, ip
 170:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 174:	7c020001 	stcvc	0, cr0, [r2], {1}
 178:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 17c:	0000001c 	andeq	r0, r0, ip, lsl r0
 180:	0000016c 	andeq	r0, r0, ip, ror #2
 184:	0000884c 	andeq	r8, r0, ip, asr #16
 188:	000000aa 	andeq	r0, r0, sl, lsr #1
 18c:	83180e41 	tsthi	r8, #1040	; 0x410
 190:	85058406 	strhi	r8, [r5, #-1030]	; 0xfffffbfa
 194:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 198:	00018e02 	andeq	r8, r1, r2, lsl #28
 19c:	00000040 	andeq	r0, r0, r0, asr #32
 1a0:	0000016c 	andeq	r0, r0, ip, ror #2
 1a4:	000088f8 	strdeq	r8, [r0], -r8	; <UNPREDICTABLE>
 1a8:	000001e0 	andeq	r0, r0, r0, ror #3
 1ac:	84180e44 	ldrhi	r0, [r8], #-3652	; 0xfffff1bc
 1b0:	86058506 	strhi	r8, [r5], -r6, lsl #10
 1b4:	88038704 	stmdahi	r3, {r2, r8, r9, sl, pc}
 1b8:	02018e02 	andeq	r8, r1, #2, 28
 1bc:	c7c8ce46 	strbgt	ip, [r8, r6, asr #28]
 1c0:	0ec4c5c6 	cdpeq	5, 12, cr12, cr4, cr6, {6}
 1c4:	180e4300 	stmdane	lr, {r8, r9, lr}
 1c8:	05850684 	streq	r0, [r5, #1668]	; 0x684
 1cc:	03870486 	orreq	r0, r7, #-2046820352	; 0x86000000
 1d0:	018e0288 	orreq	r0, lr, r8, lsl #5
 1d4:	c5c40a5e 	strbgt	r0, [r4, #2654]	; 0xa5e
 1d8:	cec8c7c6 	cdpgt	7, 12, cr12, cr8, cr6, {6}
 1dc:	0b42000e 	bleq	108021c <_stack+0x100021c>
 1e0:	0000000c 	andeq	r0, r0, ip
 1e4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 1e8:	7c020001 	stcvc	0, cr0, [r2], {1}
 1ec:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 1f0:	0000000c 	andeq	r0, r0, ip
 1f4:	000001e0 	andeq	r0, r0, r0, ror #3
 1f8:	00008ad8 	ldrdeq	r8, [r0], -r8	; <UNPREDICTABLE>
 1fc:	00000002 	andeq	r0, r0, r2
 200:	0000000c 	andeq	r0, r0, ip
 204:	000001e0 	andeq	r0, r0, r0, ror #3
 208:	00008adc 	ldrdeq	r8, [r0], -ip
 20c:	00000002 	andeq	r0, r0, r2
 210:	0000000c 	andeq	r0, r0, ip
 214:	000001e0 	andeq	r0, r0, r0, ror #3
 218:	00008ae0 	andeq	r8, r0, r0, ror #21
 21c:	00000002 	andeq	r0, r0, r2
 220:	0000000c 	andeq	r0, r0, ip
 224:	000001e0 	andeq	r0, r0, r0, ror #3
 228:	00008ae4 	andeq	r8, r0, r4, ror #21
 22c:	00000002 	andeq	r0, r0, r2
 230:	0000000c 	andeq	r0, r0, ip
 234:	000001e0 	andeq	r0, r0, r0, ror #3
 238:	00008ae8 	andeq	r8, r0, r8, ror #21
 23c:	00000002 	andeq	r0, r0, r2
 240:	0000000c 	andeq	r0, r0, ip
 244:	000001e0 	andeq	r0, r0, r0, ror #3
 248:	00008aec 	andeq	r8, r0, ip, ror #21
 24c:	00000002 	andeq	r0, r0, r2
 250:	0000000c 	andeq	r0, r0, ip
 254:	000001e0 	andeq	r0, r0, r0, ror #3
 258:	00008af0 	strdeq	r8, [r0], -r0
 25c:	00000004 	andeq	r0, r0, r4
 260:	0000000c 	andeq	r0, r0, ip
 264:	000001e0 	andeq	r0, r0, r0, ror #3
 268:	00008af4 	strdeq	r8, [r0], -r4
 26c:	00000004 	andeq	r0, r0, r4
 270:	0000000c 	andeq	r0, r0, ip
 274:	000001e0 	andeq	r0, r0, r0, ror #3
 278:	00008af8 	strdeq	r8, [r0], -r8	; <UNPREDICTABLE>
 27c:	00000002 	andeq	r0, r0, r2
 280:	0000000c 	andeq	r0, r0, ip
 284:	000001e0 	andeq	r0, r0, r0, ror #3
 288:	00008afc 	strdeq	r8, [r0], -ip
 28c:	00000002 	andeq	r0, r0, r2
 290:	0000000c 	andeq	r0, r0, ip
 294:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 298:	7c020001 	stcvc	0, cr0, [r2], {1}
 29c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 2a0:	00000020 	andeq	r0, r0, r0, lsr #32
 2a4:	00000290 	muleq	r0, r0, r2
 2a8:	00008b00 	andeq	r8, r0, r0, lsl #22
 2ac:	0000001a 	andeq	r0, r0, sl, lsl r0
 2b0:	83100e41 	tsthi	r0, #1040	; 0x410
 2b4:	85038404 	strhi	r8, [r3, #-1028]	; 0xfffffbfc
 2b8:	4a018e02 	bmi	63ac8 <__bss_end__+0x5a678>
 2bc:	c3c4c5ce 	bicgt	ip, r4, #864026624	; 0x33800000
 2c0:	0000000e 	andeq	r0, r0, lr
 2c4:	00000020 	andeq	r0, r0, r0, lsr #32
 2c8:	00000290 	muleq	r0, r0, r2
 2cc:	00008b1c 	andeq	r8, r0, ip, lsl fp
 2d0:	0000008a 	andeq	r0, r0, sl, lsl #1
 2d4:	84100e49 	ldrhi	r0, [r0], #-3657	; 0xfffff1b7
 2d8:	86038504 	strhi	r8, [r3], -r4, lsl #10
 2dc:	79018e02 	stmdbvc	r1, {r1, r9, sl, fp, pc}
 2e0:	c4c5c6ce 	strbgt	ip, [r5], #1742	; 0x6ce
 2e4:	0000000e 	andeq	r0, r0, lr

Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	6f73645f 	svcvs	0x0073645f
   4:	6e61685f 	mcrvs	8, 3, r6, cr1, cr15, {2}
   8:	00656c64 	rsbeq	r6, r5, r4, ror #24
   c:	7a69735f 	bvc	1a5cd90 <_stack+0x19dcd90>
  10:	725f0065 	subsvc	r0, pc, #101	; 0x65
  14:	34646e61 	strbtcc	r6, [r4], #-3681	; 0xfffff19f
  18:	655f0038 	ldrbvs	r0, [pc, #-56]	; ffffffe8 <_stack+0xfff7ffe8>
  1c:	6772656d 	ldrbvs	r6, [r2, -sp, ror #10]!
  20:	79636e65 	stmdbvc	r3!, {r0, r2, r5, r6, r9, sl, fp, sp, lr}^
  24:	61645f00 	cmnvs	r4, r0, lsl #30
  28:	5f006174 	svcpl	0x00006174
  2c:	74726377 	ldrbtvc	r6, [r2], #-887	; 0xfffffc89
  30:	5f626d6f 	svcpl	0x00626d6f
  34:	74617473 	strbtvc	r7, [r1], #-1139	; 0xfffffb8d
  38:	775f0065 	ldrbvc	r0, [pc, -r5, rrx]
  3c:	74727363 	ldrbtvc	r7, [r2], #-867	; 0xfffffc9d
  40:	73626d6f 	cmnvc	r2, #7104	; 0x1bc0
  44:	6174735f 	cmnvs	r4, pc, asr r3
  48:	6c006574 	cfstr32vs	mvfx6, [r0], {116}	; 0x74
  4c:	20676e6f 	rsbcs	r6, r7, pc, ror #28
  50:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
  54:	736e7520 	cmnvc	lr, #32, 10	; 0x8000000
  58:	656e6769 	strbvs	r6, [lr, #-1897]!	; 0xfffff897
  5c:	6e692064 	cdpvs	0, 6, cr2, cr9, cr4, {3}
  60:	6c5f0074 	mrrcvs	0, 7, r0, pc, cr4	; <UNPREDICTABLE>
  64:	69736662 	ldmdbvs	r3!, {r1, r5, r6, r9, sl, sp, lr}^
  68:	5f00657a 	svcpl	0x0000657a
  6c:	636f6c5f 	cmnvs	pc, #24320	; 0x5f00
  70:	5f656c61 	svcpl	0x00656c61
  74:	72610074 	rsbvc	r0, r1, #116	; 0x74
  78:	78652d6d 	stmdavc	r5!, {r0, r2, r3, r5, r6, r8, sl, fp, sp}^
  7c:	5f00632e 	svcpl	0x0000632e
  80:	7472626d 	ldrbtvc	r6, [r2], #-621	; 0xfffffd93
  84:	5f63776f 	svcpl	0x0063776f
  88:	74617473 	strbtvc	r7, [r1], #-1139	; 0xfffffb8d
  8c:	5f5f0065 	svcpl	0x005f0065
  90:	735f6d74 	cmpvc	pc, #116, 26	; 0x1d00
  94:	6c006365 	stcvs	3, cr6, [r0], {101}	; 0x65
  98:	20676e6f 	rsbcs	r6, r7, pc, ror #28
  9c:	676e6f6c 	strbvs	r6, [lr, -ip, ror #30]!
  a0:	746e6920 	strbtvc	r6, [lr], #-2336	; 0xfffff6e0
  a4:	62755f00 	rsbsvs	r5, r5, #0, 30
  a8:	5f006675 	svcpl	0x00006675
  ac:	65736162 	ldrbvs	r6, [r3, #-354]!	; 0xfffffe9e
  b0:	745f5f00 	ldrbvc	r5, [pc], #-3840	; b8 <_start-0x7f48>
  b4:	6f685f6d 	svcvs	0x00685f6d
  b8:	5f007275 	svcpl	0x00007275
  bc:	0066735f 	rsbeq	r7, r6, pc, asr r3
  c0:	5f6e6f5f 	svcpl	0x006e6f5f
  c4:	74697865 	strbtvc	r7, [r9], #-2149	; 0xfffff79b
  c8:	6772615f 			; <UNDEFINED> instruction: 0x6772615f
  cc:	635f0073 	cmpvs	pc, #115	; 0x73
  d0:	696b6f6f 	stmdbvs	fp!, {r0, r1, r2, r3, r5, r6, r8, r9, sl, fp, sp, lr}^
  d4:	5f5f0065 	svcpl	0x005f0065
  d8:	756c6773 	strbvc	r6, [ip, #-1907]!	; 0xfffff88d
  dc:	665f0065 	ldrbvs	r0, [pc], -r5, rrx
  e0:	7367616c 	cmnvc	r7, #108, 2
  e4:	73695f00 	cmnvc	r9, #0, 30
  e8:	6178635f 	cmnvs	r8, pc, asr r3
  ec:	74735f00 	ldrbtvc	r5, [r3], #-3840	; 0xfffff100
  f0:	006e6964 	rsbeq	r6, lr, r4, ror #18
  f4:	6b6c625f 	blvs	1b18a78 <_stack+0x1a98a78>
  f8:	657a6973 	ldrbvs	r6, [sl, #-2419]!	; 0xfffff68d
  fc:	76635f00 	strbtvc	r5, [r3], -r0, lsl #30
 100:	66756274 			; <UNDEFINED> instruction: 0x66756274
 104:	666f5f00 	strbtvs	r5, [pc], -r0, lsl #30
 108:	74657366 	strbtvc	r7, [r5], #-870	; 0xfffffc9a
 10c:	626d5f00 	rsbvs	r5, sp, #0, 30
 110:	6f747273 	svcvs	0x00747273
 114:	5f736377 	svcpl	0x00736377
 118:	74617473 	strbtvc	r7, [r1], #-1139	; 0xfffffb8d
 11c:	6d5f0065 	ldclvs	0, cr0, [pc, #-404]	; ffffff90 <_stack+0xfff7ff90>
 120:	656c7262 	strbvs	r7, [ip, #-610]!	; 0xfffffd9e
 124:	74735f6e 	ldrbtvc	r5, [r3], #-3950	; 0xfffff092
 128:	00657461 	rsbeq	r7, r5, r1, ror #8
 12c:	616e665f 	cmnvs	lr, pc, asr r6
 130:	00736772 	rsbseq	r6, r3, r2, ror r7
 134:	736e665f 	cmnvc	lr, #99614720	; 0x5f00000
 138:	5c3a4300 	ldcpl	3, cr4, [sl], #-0
 13c:	61746562 	cmnvs	r4, r2, ror #10
 140:	2e35725c 	mrccs	2, 1, r7, cr5, cr12, {2}
 144:	694d5c35 	stmdbvs	sp, {r0, r2, r4, r5, sl, fp, ip, lr}^
 148:	7953696e 	ldmdbvc	r3, {r1, r2, r3, r5, r6, r8, fp, sp, lr}^
 14c:	6d657473 	cfstrdvs	mvd7, [r5, #-460]!	; 0xfffffe34
 150:	7361525c 	cmnvc	r1, #92, 4	; 0xc0000005
 154:	72656270 	rsbvc	r6, r5, #112, 4
 158:	69507972 	ldmdbvs	r0, {r1, r4, r5, r6, r8, fp, ip, sp, lr}^
 15c:	6d72615c 	ldfvse	f6, [r2, #-368]!	; 0xfffffe90
 160:	0078655f 	rsbseq	r6, r8, pc, asr r5
 164:	6769735f 			; <UNDEFINED> instruction: 0x6769735f
 168:	665f006e 	ldrbvs	r0, [pc], -lr, rrx
 16c:	6b636f6c 	blvs	18dbf24 <_stack+0x185bf24>
 170:	5f00745f 	svcpl	0x0000745f
 174:	65647473 	strbvs	r7, [r4, #-1139]!	; 0xfffffb8d
 178:	5f007272 	svcpl	0x00007272
 17c:	69676942 	stmdbvs	r7!, {r1, r6, r8, fp, sp, lr}^
 180:	5f00746e 	svcpl	0x0000746e
 184:	6d6d6167 	stfvse	f6, [sp, #-412]!	; 0xfffffe64
 188:	69735f61 	ldmdbvs	r3!, {r0, r5, r6, r8, r9, sl, fp, ip, lr}^
 18c:	61676e67 	cmnvs	r7, r7, ror #28
 190:	725f006d 	subsvc	r0, pc, #109	; 0x6d
 194:	00646165 	rsbeq	r6, r4, r5, ror #2
 198:	7365725f 	cmnvc	r5, #-268435451	; 0xf0000005
 19c:	5f746c75 	svcpl	0x00746c75
 1a0:	5f5f006b 	svcpl	0x005f006b
 1a4:	47006d74 	smlsdxmi	r0, r4, sp, r6
 1a8:	4320554e 			; <UNDEFINED> instruction: 0x4320554e
 1ac:	36203131 			; <UNDEFINED> instruction: 0x36203131
 1b0:	312e332e 			; <UNDEFINED> instruction: 0x312e332e
 1b4:	31303220 	teqcc	r0, r0, lsr #4
 1b8:	32363037 	eorscc	r3, r6, #55	; 0x37
 1bc:	72282030 	eorvc	r2, r8, #48	; 0x30
 1c0:	61656c65 	cmnvs	r5, r5, ror #24
 1c4:	20296573 	eorcs	r6, r9, r3, ror r5
 1c8:	4d52415b 	ldfmie	f4, [r2, #-364]	; 0xfffffe94
 1cc:	626d652f 	rsbvs	r6, sp, #197132288	; 0xbc00000
 1d0:	65646465 	strbvs	r6, [r4, #-1125]!	; 0xfffffb9b
 1d4:	2d362d64 	ldccs	13, cr2, [r6, #-400]!	; 0xfffffe70
 1d8:	6e617262 	cdpvs	2, 6, cr7, cr1, cr2, {3}
 1dc:	72206863 	eorvc	r6, r0, #6488064	; 0x630000
 1e0:	73697665 	cmnvc	r9, #105906176	; 0x6500000
 1e4:	206e6f69 	rsbcs	r6, lr, r9, ror #30
 1e8:	34393432 	ldrtcc	r3, [r9], #-1074	; 0xfffffbce
 1ec:	205d3733 	subscs	r3, sp, r3, lsr r7
 1f0:	70666d2d 	rsbvc	r6, r6, sp, lsr #26
 1f4:	656e3d75 	strbvs	r3, [lr, #-3445]!	; 0xfffff28b
 1f8:	762d6e6f 	strtvc	r6, [sp], -pc, ror #28
 1fc:	34767066 	ldrbtcc	r7, [r6], #-102	; 0xffffff9a
 200:	666d2d20 	strbtvs	r2, [sp], -r0, lsr #26
 204:	74616f6c 	strbtvc	r6, [r1], #-3948	; 0xfffff094
 208:	6962612d 	stmdbvs	r2!, {r0, r2, r3, r5, r8, sp, lr}^
 20c:	7261683d 	rsbvc	r6, r1, #3997696	; 0x3d0000
 210:	6d2d2064 	stcvs	0, cr2, [sp, #-400]!	; 0xfffffe70
 214:	68637261 	stmdavs	r3!, {r0, r5, r6, r9, ip, sp, lr}^
 218:	6d72613d 	ldfvse	f6, [r2, #-244]!	; 0xffffff0c
 21c:	612d3776 			; <UNDEFINED> instruction: 0x612d3776
 220:	746d2d20 	strbtvc	r2, [sp], #-3360	; 0xfffff2e0
 224:	3d656e75 	stclcc	14, cr6, [r5, #-468]!	; 0xfffffe2c
 228:	74726f63 	ldrbtvc	r6, [r2], #-3939	; 0xfffff09d
 22c:	612d7865 			; <UNDEFINED> instruction: 0x612d7865
 230:	672d2037 			; <UNDEFINED> instruction: 0x672d2037
 234:	304f2d20 	subcc	r2, pc, r0, lsr #26
 238:	775f5f00 	ldrbvc	r5, [pc, -r0, lsl #30]
 23c:	00626863 	rsbeq	r6, r2, r3, ror #16
 240:	6474735f 	ldrbtvs	r7, [r4], #-863	; 0xfffffca1
 244:	0074756f 	rsbseq	r7, r4, pc, ror #10
 248:	706f6f6c 	rsbvc	r6, pc, ip, ror #30
 24c:	76635f00 	strbtvc	r5, [r3], -r0, lsl #30
 250:	6e656c74 	mcrvs	12, 3, r6, cr5, cr4, {3}
 254:	69665f00 	stmdbvs	r6!, {r8, r9, sl, fp, ip, lr}^
 258:	5f00656c 	svcpl	0x0000656c
 25c:	626f696e 	rsbvs	r6, pc, #1802240	; 0x1b8000
 260:	68730073 	ldmdavs	r3!, {r0, r1, r4, r5, r6}^
 264:	2074726f 	rsbscs	r7, r4, pc, ror #4
 268:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
 26c:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xfffff199
 270:	746e6920 	strbtvc	r6, [lr], #-2336	; 0xfffff6e0
 274:	74615f00 	strbtvc	r5, [r1], #-3840	; 0xfffff100
 278:	74697865 	strbtvc	r7, [r9], #-2149	; 0xfffff79b
 27c:	656b0030 	strbvs	r0, [fp, #-48]!	; 0xffffffd0
 280:	6c656e72 	stclvs	14, cr6, [r5], #-456	; 0xfffffe38
 284:	69616d5f 	stmdbvs	r1!, {r0, r1, r2, r3, r4, r6, r8, sl, fp, sp, lr}^
 288:	735f006e 	cmpvc	pc, #110	; 0x6e
 28c:	616e6769 	cmnvs	lr, r9, ror #14
 290:	75625f6c 	strbvc	r5, [r2, #-3948]!	; 0xfffff094
 294:	615f0066 	cmpvs	pc, r6, rrx
 298:	69746373 	ldmdbvs	r4!, {r0, r1, r4, r5, r6, r8, r9, sp, lr}^
 29c:	625f656d 	subsvs	r6, pc, #457179136	; 0x1b400000
 2a0:	5f006675 	svcpl	0x00006675
 2a4:	75736572 	ldrbvc	r6, [r3, #-1394]!	; 0xfffffa8e
 2a8:	5f00746c 	svcpl	0x0000746c
 2ac:	6863775f 	stmdavs	r3!, {r0, r1, r2, r3, r4, r6, r8, r9, sl, ip, sp, lr}^
 2b0:	4f4c5f00 	svcmi	0x004c5f00
 2b4:	545f4b43 	ldrbpl	r4, [pc], #-2883	; 2bc <_start-0x7d44>
 2b8:	6e697700 	cdpvs	7, 6, cr7, cr9, cr0, {0}
 2bc:	00745f74 	rsbseq	r5, r4, r4, ror pc
 2c0:	616c665f 	cmnvs	ip, pc, asr r6
 2c4:	00327367 	eorseq	r7, r2, r7, ror #6
 2c8:	6e756f63 	cdpvs	15, 7, cr6, cr5, cr3, {3}
 2cc:	73726574 	cmnvc	r2, #116, 10	; 0x1d000000
 2d0:	72775f00 	rsbsvc	r5, r7, #0, 30
 2d4:	00657469 	rsbeq	r7, r5, r9, ror #8
 2d8:	6d745f5f 	ldclvs	15, cr5, [r4, #-380]!	; 0xfffffe84
 2dc:	6165795f 	cmnvs	r5, pc, asr r9
 2e0:	69730072 	ldmdbvs	r3!, {r1, r4, r5, r6}^
 2e4:	7974657a 	ldmdbvc	r4!, {r1, r3, r4, r5, r6, r8, sl, sp, lr}^
 2e8:	6c006570 	cfstr32vs	mvfx6, [r0], {112}	; 0x70
 2ec:	20676e6f 	rsbcs	r6, r7, pc, ror #28
 2f0:	62756f64 	rsbsvs	r6, r5, #100, 30	; 0x190
 2f4:	5f00656c 	svcpl	0x0000656c
 2f8:	7478656e 	ldrbtvc	r6, [r8], #-1390	; 0xfffffa92
 2fc:	5f5f0066 	svcpl	0x005f0066
 300:	6d5f6d74 	ldclvs	13, cr6, [pc, #-464]	; 138 <_start-0x7ec8>
 304:	5f006e6f 	svcpl	0x00006e6f
 308:	78657461 	stmdavc	r5!, {r0, r5, r6, sl, ip, sp, lr}^
 30c:	73007469 	movwvc	r7, #1129	; 0x469
 310:	706f6275 	rsbvc	r6, pc, r5, ror r2	; <UNPREDICTABLE>
 314:	67726174 			; <UNDEFINED> instruction: 0x67726174
 318:	735f5f00 	cmpvc	pc, #0, 30
 31c:	69646964 	stmdbvs	r4!, {r2, r5, r6, r8, fp, sp, lr}^
 320:	0074696e 	rsbseq	r6, r4, lr, ror #18
 324:	66666f5f 	uqsaxvs	r6, r6, pc	; <UNPREDICTABLE>
 328:	5f00745f 	svcpl	0x0000745f
 32c:	65657266 	strbvs	r7, [r5, #-614]!	; 0xfffffd9a
 330:	7473696c 	ldrbtvc	r6, [r3], #-2412	; 0xfffff694
 334:	63775f00 	cmnvs	r7, #0, 30
 338:	626d6f74 	rsbvs	r6, sp, #116, 30	; 0x1d0
 33c:	6174735f 	cmnvs	r4, pc, asr r3
 340:	75006574 	strvc	r6, [r0, #-1396]	; 0xfffffa8c
 344:	6769736e 	strbvs	r7, [r9, -lr, ror #6]!
 348:	2064656e 	rsbcs	r6, r4, lr, ror #10
 34c:	72616863 	rsbvc	r6, r1, #6488064	; 0x630000
 350:	656e5f00 	strbvs	r5, [lr, #-3840]!	; 0xfffff100
 354:	685f0077 	ldmdavs	pc, {r0, r1, r2, r4, r5, r6}^	; <UNPREDICTABLE>
 358:	7272655f 	rsbsvc	r6, r2, #398458880	; 0x17c00000
 35c:	73006f6e 	movwvc	r6, #3950	; 0xf6e
 360:	74726f68 	ldrbtvc	r6, [r2], #-3944	; 0xfffff098
 364:	746e6920 	strbtvc	r6, [lr], #-2336	; 0xfffff6e0
 368:	745f5f00 	ldrbvc	r5, [pc], #-3840	; 370 <_start-0x7c90>
 36c:	64795f6d 	ldrbtvs	r5, [r9], #-3949	; 0xfffff093
 370:	5f007961 	svcpl	0x00007961
 374:	7562735f 	strbvc	r7, [r2, #-863]!	; 0xfffffca1
 378:	695f0066 	ldmdbvs	pc, {r1, r2, r5, r6}^	; <UNPREDICTABLE>
 37c:	0073626f 	rsbseq	r6, r3, pc, ror #4
 380:	49465f5f 	stmdbmi	r6, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, ip, lr}^
 384:	5f00454c 	svcpl	0x0000454c
 388:	7473626d 	ldrbtvc	r6, [r3], #-621	; 0xfffffd93
 38c:	5f657461 	svcpl	0x00657461
 390:	5f5f0074 	svcpl	0x005f0074
 394:	4c494673 	mcrrmi	6, 7, r4, r9, cr3
 398:	6d5f0045 	ldclvs	0, cr0, [pc, #-276]	; 28c <_start-0x7d74>
 39c:	61747362 	cmnvs	r4, r2, ror #6
 3a0:	5f006574 	svcpl	0x00006574
 3a4:	646e6172 	strbtvs	r6, [lr], #-370	; 0xfffffe8e
 3a8:	78656e5f 	stmdavc	r5!, {r0, r1, r2, r3, r4, r6, r9, sl, fp, sp, lr}^
 3ac:	6d5f0074 	ldclvs	0, cr0, [pc, #-464]	; 1e4 <_start-0x7e1c>
 3b0:	6e656c62 	cdpvs	12, 6, cr6, cr5, cr2, {3}
 3b4:	6174735f 	cmnvs	r4, pc, asr r3
 3b8:	5f006574 	svcpl	0x00006574
 3bc:	00636e69 	rsbeq	r6, r3, r9, ror #28
 3c0:	646e695f 	strbtvs	r6, [lr], #-2399	; 0xfffff6a1
 3c4:	6f6c5f00 	svcvs	0x006c5f00
 3c8:	656c6163 	strbvs	r6, [ip, #-355]!	; 0xfffffe9d
 3cc:	635f5f00 	cmpvs	pc, #0, 30
 3d0:	6e61656c 	cdpvs	5, 6, cr6, cr1, cr12, {3}
 3d4:	5f007075 	svcpl	0x00007075
 3d8:	70736e75 	rsbsvc	r6, r3, r5, ror lr
 3dc:	66696365 	strbtvs	r6, [r9], -r5, ror #6
 3e0:	5f646569 	svcpl	0x00646569
 3e4:	61636f6c 	cmnvs	r3, ip, ror #30
 3e8:	695f656c 	ldmdbvs	pc, {r2, r3, r5, r6, r8, sl, sp, lr}^	; <UNPREDICTABLE>
 3ec:	006f666e 	rsbeq	r6, pc, lr, ror #12
 3f0:	78616d5f 	stmdavc	r1!, {r0, r1, r2, r3, r4, r6, r8, sl, fp, sp, lr}^
 3f4:	00736477 	rsbseq	r6, r3, r7, ror r4
 3f8:	6565725f 	strbvs	r7, [r5, #-607]!	; 0xfffffda1
 3fc:	5f00746e 	svcpl	0x0000746e
 400:	64656573 	strbtvs	r6, [r5], #-1395	; 0xfffffa8d
 404:	635f5f00 	cmpvs	pc, #0, 30
 408:	746e756f 	strbtvc	r7, [lr], #-1391	; 0xfffffa91
 40c:	6c5f5f00 	mrrcvs	15, 0, r5, pc, cr0	; <UNPREDICTABLE>
 410:	006b636f 	rsbeq	r6, fp, pc, ror #6
 414:	61765f5f 	cmnvs	r6, pc, asr pc
 418:	0065756c 	rsbeq	r7, r5, ip, ror #10
 41c:	6565735f 	strbvs	r7, [r5, #-863]!	; 0xfffffca1
 420:	665f006b 	ldrbvs	r0, [pc], -fp, rrx
 424:	5f736f70 	svcpl	0x00736f70
 428:	5f5f0074 	svcpl	0x005f0074
 42c:	6d5f6d74 	ldclvs	13, cr6, [pc, #-464]	; 264 <_start-0x7d9c>
 430:	5f006e69 	svcpl	0x00006e69
 434:	746c756d 	strbtvc	r7, [ip], #-1389	; 0xfffffa93
 438:	74735f00 	ldrbtvc	r5, [r3], #-3840	; 0xfffff100
 43c:	6b6f7472 	blvs	1bdd60c <_stack+0x1b5d60c>
 440:	73616c5f 	cmnvc	r1, #24320	; 0x5f00
 444:	665f0074 			; <UNDEFINED> instruction: 0x665f0074
 448:	7079746e 	rsbsvc	r7, r9, lr, ror #8
 44c:	5f007365 	svcpl	0x00007365
 450:	00646461 	rsbeq	r6, r4, r1, ror #8
 454:	4c555f5f 	mrrcmi	15, 5, r5, r5, cr15	; <UNPREDICTABLE>
 458:	00676e6f 	rsbeq	r6, r7, pc, ror #28
 45c:	7465675f 	strbtvc	r6, [r5], #-1887	; 0xfffff8a1
 460:	65746164 	ldrbvs	r6, [r4, #-356]!	; 0xfffffe9c
 464:	7272655f 	rsbsvc	r6, r2, #398458880	; 0x17c00000
 468:	6c675f00 	stclvs	15, cr5, [r7], #-0
 46c:	6c61626f 	sfmvs	f6, 2, [r1], #-444	; 0xfffffe44
 470:	706d695f 	rsbvc	r6, sp, pc, asr r9
 474:	5f657275 	svcpl	0x00657275
 478:	00727470 	rsbseq	r7, r2, r0, ror r4
 47c:	756e755f 	strbvc	r7, [lr, #-1375]!	; 0xfffffaa1
 480:	5f646573 	svcpl	0x00646573
 484:	646e6172 	strbtvs	r6, [lr], #-370	; 0xfffffe8e
 488:	64775f00 	ldrbtvs	r5, [r7], #-3840	; 0xfffff100
 48c:	5f5f0073 	svcpl	0x005f0073
 490:	775f6d74 			; <UNDEFINED> instruction: 0x775f6d74
 494:	00796164 	rsbseq	r6, r9, r4, ror #2
 498:	756c675f 	strbvc	r6, [ip, #-1887]!	; 0xfffff8a1
 49c:	6e5f0065 	cdpvs	0, 5, cr0, cr15, cr5, {3}
 4a0:	6c6c616d 	stfvse	f6, [ip], #-436	; 0xfffffe4c
 4a4:	5f00636f 	svcpl	0x0000636f
 4a8:	6134366c 	teqvs	r4, ip, ror #12
 4ac:	6675625f 			; <UNDEFINED> instruction: 0x6675625f
 4b0:	69735f00 	ldmdbvs	r3!, {r8, r9, sl, fp, ip, lr}^
 4b4:	75665f67 	strbvc	r5, [r6, #-3943]!	; 0xfffff099
 4b8:	6100636e 	tstvs	r0, lr, ror #6
 4bc:	73676174 	cmnvc	r7, #116, 2
 4c0:	69706700 	ldmdbvs	r0!, {r8, r9, sl, sp, lr}^
 4c4:	6e5f006f 	cdpvs	0, 5, cr0, cr15, cr15, {3}
 4c8:	00667562 	rsbeq	r7, r6, r2, ror #10
 4cc:	756e755f 	strbvc	r7, [lr, #-1375]!	; 0xfffffaa1
 4d0:	00646573 	rsbeq	r6, r4, r3, ror r5
 4d4:	6d745f5f 	ldclvs	15, cr5, [r4, #-380]!	; 0xfffffe84
 4d8:	6473695f 	ldrbtvs	r6, [r3], #-2399	; 0xfffff6a1
 4dc:	5f007473 	svcpl	0x00007473
 4e0:	61636f6c 	cmnvs	r3, ip, ror #30
 4e4:	6d69746c 	cfstrdvs	mvd7, [r9, #-432]!	; 0xfffffe50
 4e8:	75625f65 	strbvc	r5, [r2, #-3941]!	; 0xfffff09b
 4ec:	635f0066 	cmpvs	pc, #102	; 0x66
 4f0:	65736f6c 	ldrbvs	r6, [r3, #-3948]!	; 0xfffff094
 4f4:	34725f00 	ldrbtcc	r5, [r2], #-3840	; 0xfffff100
 4f8:	6d5f0038 	ldclvs	0, cr0, [pc, #-224]	; 420 <_start-0x7be0>
 4fc:	776f7462 	strbvc	r7, [pc, -r2, ror #8]!
 500:	74735f63 	ldrbtvc	r5, [r3], #-3939	; 0xfffff09d
 504:	00657461 	rsbeq	r7, r5, r1, ror #8
 508:	7335705f 	teqvc	r5, #95	; 0x5f
 50c:	745f5f00 	ldrbvc	r5, [pc], #-3840	; 514 <_start-0x7aec>
 510:	646d5f6d 	strbtvs	r5, [sp], #-3949	; 0xfffff093
 514:	5f007961 	svcpl	0x00007961
 518:	6c796164 	ldfvse	f6, [r9], #-400	; 0xfffffe70
 51c:	74686769 	strbtvc	r6, [r8], #-1897	; 0xfffff897
 520:	6d726100 	ldfvse	f6, [r2, #-0]
 524:	39302d63 	ldmdbcc	r0!, {r0, r1, r5, r6, r8, sl, fp, sp}
 528:	7473632d 	ldrbtvc	r6, [r3], #-813	; 0xfffffcd3
 52c:	2e736275 	mrccs	2, 3, r6, cr3, cr5, {3}
 530:	745f0063 	ldrbvc	r0, [pc], #-99	; 538 <_start-0x7ac8>
 534:	6d616e7a 	stclvs	14, cr6, [r1, #-488]!	; 0xfffffe18
 538:	72700065 	rsbsvc	r0, r0, #101	; 0x65
 53c:	685f7665 	ldmdavs	pc, {r0, r2, r5, r6, r9, sl, ip, sp, lr}^	; <UNPREDICTABLE>
 540:	5f706165 	svcpl	0x00706165
 544:	00646e65 	rsbeq	r6, r4, r5, ror #28
 548:	72636e69 	rsbvc	r6, r3, #1680	; 0x690
 54c:	69745f00 	ldmdbvs	r4!, {r8, r9, sl, fp, ip, lr}^
 550:	6f7a656d 	svcvs	0x007a656d
 554:	6300656e 	movwvs	r6, #1390	; 0x56e
 558:	72646461 	rsbvc	r6, r4, #1627389952	; 0x61000000
 55c:	5f00745f 	svcpl	0x0000745f
 560:	6b726273 	blvs	1c98f34 <_stack+0x1c18f34>
 564:	625f5f00 	subsvs	r5, pc, #0, 30
 568:	655f7373 	ldrbvs	r7, [pc, #-883]	; 1fd <_start-0x7e03>
 56c:	5f5f646e 	svcpl	0x005f646e
 570:	73635f00 	cmnvc	r3, #0, 30
 574:	74726174 	ldrbtvc	r6, [r2], #-372	; 0xfffffe8c
 578:	61007075 	tstvs	r0, r5, ror r0
 57c:	2d636d72 	stclcs	13, cr6, [r3, #-456]!	; 0xfffffe38
 580:	632d3930 			; <UNDEFINED> instruction: 0x632d3930
 584:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
 588:	2e707574 	mrccs	5, 3, r7, cr0, cr4, {3}
 58c:	73620063 	cmnvc	r2, #99	; 0x63
 590:	6e655f73 	mcrvs	15, 3, r5, cr5, cr3, {3}
 594:	5f5f0064 	svcpl	0x005f0064
 598:	5f737362 	svcpl	0x00737362
 59c:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
 5a0:	005f5f74 	subseq	r5, pc, r4, ror pc	; <UNPREDICTABLE>

Disassembly of section .ARM.attributes:

00000000 <_stack-0x80000>:
   0:	00003241 	andeq	r3, r0, r1, asr #4
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000028 	andeq	r0, r0, r8, lsr #32
  10:	412d3705 			; <UNDEFINED> instruction: 0x412d3705
  14:	070a0600 	streq	r0, [sl, -r0, lsl #12]
  18:	09010841 	stmdbeq	r1, {r0, r6, fp}
  1c:	0c050a02 			; <UNDEFINED> instruction: 0x0c050a02
  20:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
  28:	1a011803 	bne	4603c <__bss_end__+0x3cbec>
  2c:	1e011c01 	cdpne	12, 0, cr1, cr1, cr1, {0}
  30:	Address 0x00000030 is out of bounds.

