/* $MirOS: src/sys/arch/i386/stand/bootxx/bootxx.S,v 1.22 2009/06/29 20:01:45 tg Exp $ */

/*-
 * Copyright (c) 2009
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

	.intel_syntax noprefix
	.section .comment
	.asciz	"$MirOS: src/sys/arch/i386/stand/bootxx/bootxx.S,v 1.22 2009/06/29 20:01:45 tg Exp $"

	.code16
	.text

	.globl	_start
	.type	_start,@function
_start:	/* bootxx entry point 07C00 */
	xor	ecx,ecx
	mov	ss,cx
	mov	sp,0x7BFC
	push	ecx
	popfd
	mov	es,cx
	mov	di,0x7C00	/* 0000:_start pre-reloc */
	push	di
	/* save partition table entry */
	mov	cl,16
	rep	movsb
	pop	si
	mov	ds,cx
	mov	bx,SA_LINKSEG
	push	bx
	push	bx
	mov	es,bx
	mov	di,offset _start
	mov	ch,2		/* 512 bytes */
	rep	movsb
	pop	ds
	push	offset Lmain
	lret

	Lpblk = _start + 0x10
	Lebss = Lpblk + 0x18	/* make sure this is < Lmmsg */

Lemsg:	.ascii	__BOOT_VER
	.asciz	" Loading "
Lmmsg:	.ascii	"bad magic"
Lfmsg:	.ascii	" error"
Lbmsg:	.asciz	"\r\n"

	.globl	bkcnt
	.type	bkcnt,@object
	.size	bkcnt,1
bkcnt:	.byte	(bkend - bktbl)

	.globl	geomh
	.type	geomh,@object
	.size	geomh,2
geomh:	.word	2		/* 1..256 = tracks per cylinder */

	.globl	geoms
	.type	geoms,@object
	.size	geoms,2
	/* set to 0 for auto geometry */
geoms:	.word	18		/* 1..63 = sectors per track */

	.globl	partp
	.type	partp,@object
	.size	partp,1
partp:	.byte	0
Ldrv:	.byte	0x80		/* must be at partp + 1 */

Lload:	.word	LsLBA

	/* output NUL-terminated string from ds:si */
Lotxt0:	mov	ah,0x0E
	mov	bx,7
	int	0x10
Lotxt:	lodsb
	or	al,al
	jnz	Lotxt0
	ret

Lbarf:	call	Lotxt
	mov	ax,offset LsCHS
	xchg	ax,[Lload]
	cmp	ax,offset LsCHS
	jne	Lretr
	xor	ax,ax
	int	0x16
	jmp	0xF000,0xFFF0

Lmain:	sti
	mov	[Ldrv],dl
	mov	si,offset Lemsg
	cmp	dl,0x80
	jb	Lbarf		/* floppy: only try CHS */
	call	Lotxt
	/* FALLTHROUGH */

Lretr:	xor	bx,bx		/* load offset (begin) */
	mov	si,offset bktbl
	movzx	bp,byte ptr [bkcnt]
Lloop:	lodsb
	/*-
	 * AL contains bitmasked:  aaabbbbb
	 * -> a = (number of bytes - 1) that follow	(-> CX)
	 * -> b = (number of sectors - 1) to load	(-> DI)
	 * BX contains current load address offset
	 * SI contains pointer to data being processed
	 * BP contains number of entries to process
	 */

	/* decode */
	movzx	cx,al
	shr	cl,5
	and	ax,0x1F
	inc	ax
	inc	cx
	push	ax		/* later DI */

	/* create LBA parameter block */
	mov	di,offset Lpblk
	mov	ax,0x0010
	stosw
	mov	al,1
	stosw
	mov	ax,bx
	stosw
	mov	ax,cs
	stosw
	rep	movsb		/* copy CX bytes */
	xor	ax,ax		/* pad with 8 (up to 7 needed) NUL bytes */
	stosw
	stosw
	stosw
	stosw

	pop	di
	/*-
	 * Lpblk, Ldrv are filled in completely
	 * CS = DS = ES = SA_LINKSEG = 0x4000
	 * DI = number of sectors to still load
	 * BX = load offset (segment CS)
	 * BP = number of entries to load, including this one
	 * SI = pointer to next entry to load
	 */
	push	bp
	push	si
Lld1s:	mov	si,offset Lpblk
	call	[Lload]
	mov	bp,4		/* number of retries */
	mov	dl,[Ldrv]
Lldlp:	pusha
	stc
	int	0x13
	pushf
	mov	ax,0x0E2E	/* "dot" as progress meter */
	mov	bx,7
	int	0x10
	popf
	sti
	popa
	jnc	Lldok
	dec	bp
	pusha
	pushf
	xor	ax,ax		/* reset drive */
	int	0x13
	popf
	mov	si,offset Lfmsg
	jz	Lbarf
	mov	ax,0x0E30	/* number as fail meter */
	add	ax,bp
	mov	bx,7
	int	0x10
	popa
	jmp	Lldlp
Lldok:	/* increment load address by sector size */
	mov	ah,2		/* 512 bytes */
	.globl	secsz
	.type	secsz,@object
	.size	secsz,1
	secsz = . - 1		/* the "2" above */
L...1:	add	bh,ah		/* add the 512 bytes */
	mov	4[si],bx
	add	ah,bh		/* again */
	jc	Ldone		/* last block completes (64 KiB - bootxx) */
	/* increment quadword by one */
	add	dword ptr 8[si],1
	adc	dword ptr 12[si],0
	/* load next sector */
	dec	di
	jnz	Lld1s
	pop	si
	pop	bp
	dec	bp
	jnz	Lloop
	/* FALLTHROUGH */

Ldone:	/* check bootloader magic */
#ifndef BOOT_GRUB
	xor	eax,eax
	push	ax		/* return address */
	mov	ax,[partp]
	xchg	eax,ds:[4]	/* location of magic in /boot */
	cmp	eax,0x696D4F00
	mov	si,offset Lmmsg
	jne	Lbarf
#endif
	mov	si,offset Lbmsg
	call	Lotxt
#ifndef BOOT_GRUB
	mov	si,offset _start
	ret
#else
	xor	edx,edx
	push	dx		/* initial CS */
	dec	edx		/* EDX := FFFFFFFF */
	mov	dl,[Ldrv]	/* boot BIOS drive number */
	mov	ax,0x8200
	push	ax		/* initial IP */
	cli			/* be nice to a GNU every once in a while */
	lret
#endif

	/* obtain drive geometry */
Lgeom:	pusha
	push	es
#if 0
	/*
	 * According to RBIL, this is needed to guard against
	 * BIOS bugs, but we don’t read out the table anyway.
	 */
	xor	di,di
	mov	es,di
#endif
	mov	ah,8
	mov	dl,[Ldrv]
	stc
	int	0x13
	sti
	pop	es
	mov	si,offset Lfmsg
	jc	Lbarf
	/* process returned values */
	and	cl,0x3F		/* number of sectors per track */
	mov	[geoms],cl	/* high byte is 0 anyway */
	movzx	ax,dh
	inc	ax		/* maximum index -> number of heads */
	mov	[geomh],ax
	popa
	/* FALLTHROUGH */

LsCHS:	mov	cx,[geoms]
	jcxz	Lgeom
	mov	ax,8[si]
	mov	dx,10[si]
	div	cx
	inc	dx		/* remainder: sector */
	xor	cx,cx
	xchg	cx,dx
	div	word ptr [geomh]
	shl	ah,6		/* quotient: cylinder */
	xchg	ah,al
	or	cx,ax
	mov	dh,dl		/* remainder: head */
	mov	ax,0x0201
	ret

LsLBA:	mov	ah,0x42
	ret

	.globl	bktbl
	.type	bktbl,@object
bktbl:	.long	0xCAFEBABE

	/* ensure we have space for a partition table */
	. = _start + 0x01BE
	.byte	0

	/* bxinst requires bktbl to end at 510 */
	. = _start + 0x01FE
	/* bkend is required by installboot(8) still */
	.globl	bkend
	.type	bkend,@object
bkend:	.word	0xAA55
