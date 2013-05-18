/* $MirOS: src/sys/arch/i386/stand/bootxx/bootxx.S,v 1.13 2009/01/10 23:52:48 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2007, 2009
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
	.code16
	.text

	.type	_start, @function
	.globl	_start
_start:
	xor	ax,ax
	push	ax
	popf
	/* set up stack from 07C0:FFFC (0x17BFC) down */
	add	ax,0x07C0
	mov	ss,ax
	mov	sp,0xFFFC
	push	ds
	push	si
	push	ax		/* for retf */
	push	offset Lmain
	/* set up code and data at 07C0:0000 (0x07C00) = 0000:7C00 up */
	mov	ds,ax
	mov	es,ax
	/* jump to 'cs:offset Lmain' */
	lret

Lmsg:	.ascii	__BOOT_VER
	.asciz	" Loading "

Lerr:	.ascii	"bad magic"
Lldf:	.ascii	" ERR"
Lcrlf:	.asciz	"\r\n"

#define BLKCNT	(blkend - blktbl)
	.size	blkcnt, 1
	.type	blkcnt, @object
	.globl	blkcnt
blkcnt:	.byte	BLKCNT

Lldp:	.word	LsLBA

	.size	partp, 1
	.type	partp, @object
	.globl	partp
partp:	.byte	0		/* must be Ldrv - 1 */
Ldrv:	.byte	0x80

	.size	bpbspt, 2
	.type	bpbspt, @object
	.globl	bpbspt
bpbspt:	.word	18

	.size	bpbtpc, 2
	.type	bpbtpc, @object
	.globl	bpbtpc
bpbtpc:	.word	2

	/* output NUL-terminated string from ds:si */
	.globl	Lotxt
Lotxt0:	mov	ah,0x0E
	mov	bx,7
	int	0x10
Lotxt:	lodsb
	or	al,al
	jnz	Lotxt0
	ret

	/* If something went wrong, but we didn't yet try the subrouting
	 * to cope with broken BIOSes and Soekris, redo from start.
	 */
Lbarf:	call	Lotxt			/* something went wrong */
	mov	ax,offset LsBRK		/* offset of broken-BIOS load sub */
	xchg	ax,[Lldp]
	cmp	ax,offset LsBRK		/* broken BIOS sub already tried? */
	jne	LbLBA
	xor	ah,ah
	int	0x16
	jmp	0xF000,0xFFF0

Lmain:	mov	[Ldrv],dl	/* save boot device */
	/* say hello */
	mov	si,offset Lmsg
	call	Lotxt
	/* check for single-block CHS */
	mov	ax,offset LsBRK
	xchg	bh,[bpbspt+1]
	and	bh,0x80
	jnz	LbCHS		/* yep, hardcoded via bootloader */
	push	ax
	mov	ah,2		/* get shift state of keyboard */
	int	0x16
	and	al,3		/* any shift key pressed? */
	pop	ax
	jnz	LbCHS		/* if so, go to single sector mode */
	/* check for LBA vs. CHS */
	mov	ah,0x41		/* LBA installation check */
	mov	bx,0x55AA	/* magic */
	int	0x13
	mov	ax,offset LsCHS
	jc	LbCHS		/* CF set -> nope, use CHS */
	cmp	bx,0xAA55	/* magic */
	jne	LbCHS		/* bad magic -> nope, use CHS */
	and	cl,1		/* API subset support bitmap */
	jnz	LbLBA		/* extended disc access funcs supported */

LbCHS:	mov	word ptr ds:[Lldp],ax
LbLBA:	xor	di,di
	push	di		/* 0 */
	mov	ax,0x0010
	stosw
	push	di		/* 2 */
	mov	ax,SA_LINKSEG	/* libsa constant */
	mov	fs,ax		/* for magic check and booting */
	push	ax		/* running counter, for loading */
	mov	si,offset blktbl
	mov	cl,[blkcnt]
Lmlp1:	/* main load loop */
	xor	eax,eax
	lodsb
	/*
	 * al contains bitmasked:
	 * aaabbbbb
	 * -> a=number of bytes-1 that follow	(-> dl)
	 * -> b=number of sectors-1 to load	(-> al)
	 * si, cl contain what is to be processed
	 */

	pop	bx
	pop	di
	push	di

	/* decode */
	mov	dl,al
	shr	dl,5
	and	al,0x1F
	inc	ax
	inc	dx
	stosd

	xchg	ax,bx		/* load segment */
	stosw
	shl	bx,(9 - 4)	/* number of sectors, times their size,
				   divided by size of one paragraph */
	secsizofs = . - 1
	.globl	secsizofs
	.size	secsizofs, 1
	add	bx,ax		/* increment load addr. segment accordingly */
	push	bx		/* and save for next round */
	push	cx		/* save blkcnt */

Lmlp2:	movsb			/* copy over as many bytes as needed */
	dec	dl
	jne	Lmlp2
	xor	ax,ax		/* pad with up to 7 NUL-bytes */
	stosw
	stosw
	stosw
	stosw

	/*
	 * at this point, we have the following:
	 * si points to the _next_ entry to load
	 * on top of stack, there is the number of
	 *    entries to load, including the current one
	 * the _next_ load address is below that on the stack
	 * below that, 0x0002 (for DI) is on the stack
	 * the LBA parameter block is filled in.
	 * BX is set up to the load segment (offset = const. 0000)
	 */
	/* call subroutine that does the actual loading */
	mov	dl,[Ldrv]
	call	[Lldp]
	/* and loop back */
	pop	cx
	dec	cl
	jne	Lmlp1

	/* ok, second-stage boot loader is in memory, starting FS:[0000] */
	xor	eax,eax
	mov	ax,[partp]
	/* check some "random" ASCII string, i.e. the boot magic */
	xchg	eax,fs:[4]
	cmp	eax,0x6A6D4F00
	mov	si,offset Lerr		/* "bad magic" */
	jne	Lbarf			/* it isn't correct, barf out */
	/* new line, for the fine look */
	mov	si,offset Lcrlf
	call	Lotxt
	/* set up and jump into /boot */
	pop	si			/* running counter */
	pop	si			/* 2 */
	pop	cx			/* 0 */
	pop	si			/* original SI */
	pop	ds			/* original DS */
	push	fs			/* load segment */
	push	cx			/* 0 */
	lret

	/* LBA boot routine */
LsLBA:	push	si			/* save blktbl offset */
	mov	ah,0x42			/* BIOS routine loadLBA */
	xor	si,si			/* offset parblk */
	call	LsINT			/* call BIOS subroutine */
	pop	si
Lretn:	ret

	/* some broken BIOSes don't allow multi-sector transfers... */
LsBRK:	mov	dh,1
	xchg	dh,ds:[2]		/* number of sectors to load */
LsBR0:	push	dx
	call	LsCHS			/* chain to default CHS loader */
	pop	dx
	dec	dh
	je	Lretn			/* loop one by one over the sectors */
	add	word ptr ds:[6],32	/* size of a sector in paragraphs */
	inc	dword ptr ds:[8]
	jmp	LsBR0

	/* CHS boot routine */
LsCHS:	push	dx
	/* LBA -> CHS */
	mov	ax,ds:[8]
	mov	dx,ds:[10]
	div	word ptr [bpbspt]
	inc	dx			/* quotient AX, remainder DX */
	push	dx			/* sector */
	xor	dx,dx
	div	word ptr [bpbtpc]
	pop	cx			/* cylinder AX, head DX */
	shl	ah,6
	xchg	ah,al
	or	cx,ax
	mov	dh,dl
	pop	ax
	mov	dl,al
	/* call the BIOS */
	mov	ah,2
	mov	al,ds:[2]
	xor	bx,bx

	/* call the interrupt */
LsINT:	mov	bp,4			/* number of retries */
LsIN0:	pusha
	mov	es,ds:[6]
	int	0x13
	push	ds
	pop	es
	/* progress meter */
	pushf
	mov	ax,0x0E2E
	mov	bx,7
	int	0x10			/* output a dot */
	popf
	popa
	jnc	Lretn
	dec	bp
	pusha
	mov	si,offset Lldf
	jz	Lbarf
	mov	ax,0x0E30		/* say it fails */
	add	ax,bp
	mov	bx,7
	int	0x10
	xor	ax,ax
	int	0x13
	popa
	jmp	LsIN0

	.type	blktbl, @object
	.globl	blktbl
blktbl:
	/* free space for block table till end of sector */

	. = 0x1FE
	.size	blkend, 2
	.globl	blkend
blkend:
	.word	0xAA55
