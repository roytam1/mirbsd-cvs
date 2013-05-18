/* $MirOS: src/sys/arch/i386/stand/bootxx/bootxx.S,v 1.9 2007/09/28 20:51:27 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <machine/asm.h>

#define LDENTRY(x)	OTYPE(_ASM_LABEL(x)); _ASM_LABEL(x):
#define LTENTRY(x)	FTYPE(_ASM_LABEL(x)); _ASM_LABEL(x):
#define GDENTRY(x)	.globl _ASM_LABEL(x); LDENTRY(x)
#define GTENTRY(x)	.globl _ASM_LABEL(x); LTENTRY(x)

	.intel_syntax noprefix
	.code16
	.text

GTENTRY(_start)
	xor	eax,eax
	push	eax
	popfd
	/* set up stack from 07C0:FFFC (0x17BFC) down */
	add	ax,0x07C0
	mov	ss,ax
	mov	sp,0xFFFC
	sti
	push	ax		/* for retf */
	push	offset Lmain
	/* set up code and data at 07C0:0000 (0x07C00) = 0000:7C00 up */
	mov	ds,ax
	mov	es,ax
	/* jump to 'cs:offset Lmain' */
	lret

LDENTRY(Lmsg)
	.ascii	__BOOT_VER
	.asciz	" Loading "

LDENTRY(Lerr)
	.ascii	"bad magic"
LDENTRY(Lldf)
	.ascii	" ERR"
LDENTRY(Lcrlf)
	.asciz	"\r\n"

#define BLKCNT	(blkend - blktbl)
	.size	blkcnt, 1
GDENTRY(blkcnt)
	.byte	BLKCNT

LDENTRY(Lldp)
	.word	LsLBA

LDENTRY(Ldrv)
	.byte	0x80
	.size	partp, 1
GDENTRY(partp)
	.byte	0		/* must be Ldrv + 1 */

	.size	bpbspt, 2
GDENTRY(bpbspt)
	.word	18

	.size	bpbtpc, 2
GDENTRY(bpbtpc)
	.word	2

	/* output NUL-terminated string from ds:si */
LTENTRY(Lotxt0)
	mov	ah,0x0E
	mov	bx,7
	int	0x10
GTENTRY(Lotxt)
	lodsb
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

LTENTRY(Lmain)
	mov	[Ldrv],dl	/* save boot device */
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
	mov	ax,0x0010
	stosw
	push	di
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
	push	fs
	push	cx
	/* check some "random" ASCII string, i.e. the boot magic */
	mov	eax,0x6A6D4F00
	/* manipulate here, but first byte MBZ */
	magicofs = . - 3
	.globl	magicofs

	xchg	eax,dword ptr fs:[0x50]
	cmp	eax,0x6A6D4F00
	mov	si,offset Lerr		/* "bad magic" */
	jne	Lbarf			/* it isn't correct, barf out */
	/* new line, for the fine look */
	mov	si,offset Lcrlf
	call	Lotxt
	/* set up and jump into /boot */
	mov	dx,[Ldrv]
	mov	fs:[0x50],dh
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

GDENTRY(blktbl)
	/* free space for block table till end of sector */

	. = 0x1FE
	.size	blkend, 2
GDENTRY(blkend)
	.word	0xAA55
