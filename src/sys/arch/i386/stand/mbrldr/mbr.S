/* $MirOS: src/sys/arch/i386/stand/mbrldr/mbr.S,v 1.2 2005/04/19 13:24:10 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Just Another Rewritten Master/Partition boot record
 * chainable, loads two 512-byte sectors at once, could run /boot too
 */

	.intel_syntax noprefix
	.code16
	.text
	.globl	_start

_start:	xor	ax,ax
	push	ax
	popf
	add	ax,0x07A0
	mov	ss,ax
	mov	sp,0xFFFC
	sti
	push	ax
	mov	ds,ax
	mov	es,ax
	mov	si,0x0200
	xor	di,di
	mov	cx,si
	rep	movsb
	push	offset Lmain
	lret

Lmsg:	.ascii	"Mir-" __BOOT_VER
#ifdef	BOOTMANAGER
	.ascii	": 0="
Lm00:	.ascii	"00 1="
Lm01:	.ascii	"00 2="
Lm02:	.ascii	"00 3="
Lm03:	.ascii	"00 4=MBR 5=fd CR=std\r\n"
#endif
	.asciz	">"

Lotxt:	lodsb
	or	al,al
	jne	Lotxt_
	ret
Lotxt_:	mov	ah,0x0E
	mov	bx,7
	int	0x10
	jmp	Lotxt

#ifdef	BOOTMANAGER
Lmod:	mov	di,offset Lm00
	mov	al,ds:[0x01C2]
	call	LpBY
	mov	di,offset Lm01
	mov	al,ds:[0x01D2]
	call	LpBY
	mov	di,offset Lm02
	mov	al,ds:[0x01E2]
	call	LpBY
	mov	di,offset Lm03
	mov	al,ds:[0x01F2]
LpBY:	mov	ah,al
	shr	al,4
	and	ah,0x0F
	add	ax,0x3030
	cmp	al,0x39
	jbe	LpBY1
	add	al,7
LpBY1:	cmp	ah,0x39
	jbe	LpBY2
	add	ah,7
LpBY2:	stosw
	ret
#endif

Ltry:	mov	bp,4
	call	Ltry0
	jc	Ltry1
	cmp	ah,0x42
	je	Ltry2
	inc	cx
	add	bh,2
	jmp	Ltry3
Ltry2:	add	byte ptr ds:[5],2
	inc	dword ptr ds:[8]
Ltry3:	call	Ltry0
	push	dx
	mov	ax,0x0E0D	/* magic -> this pbr */
	mov	ds:[0x600],ax	/* at 0x08000 linear */
	xor	bx,bx
	int	0x10
	pop	dx
	cli			/* be nice :) */
	jmp	0,0x7C00
Ltry0:	pusha
	int	0x13
	popa
	jnc	Ltry1
	pusha
	xor	ax,ax
	int	0x13
	popa
	dec	bp
	jne	Ltry0
	stc
Ltry1:	ret

Lmain:	mov	si,offset Lmsg
#ifdef	BOOTMANAGER
	call	Lmod
#endif
	call	Lotxt
	mov	bx,0x01BE	/* partition table offset */
#ifdef	BOOTMANAGER
	xor	ax,ax		/* read CMOS clock ticks since midnight */
	int	0x1A
	add	dx,183		/* 10 seconds rounded up one tick */
	Ltimeout = . - 2
	adc	cl,0		/* carry over */
	shl	ecx,16
	mov	cx,dx
	mov	edi,ecx
Lilp:	mov	ah,1		/* check if key pressed */
	int	0x16
	jnz	Lkeyp		/* key was pressed */
	xor	ax,ax
	int	0x1A
	shl	ecx,16
	mov	cx,dx		/* current clock tick */
	or	al,al		/* past midnight? */
	jz	Lsame
	add	ecx,1573040	/* according to Ralf Brown Interrupt List */
Lsame:	cmp	ecx,edi		/* time is over? */
	jbe	Lilp		/* not yet */
	jmp	Lscanp		/* assume user pressed RETURN (default) */
Lkeyp:	xor	ah,ah		/* get pressed key */
	int	0x16
	sub	al,13		/* return */
	jb	Lkeyp		/* illegal */
	je	Lscanp
	sub	al,0x30-13	/* '0' */
	jb	Lkeyp		/* illegal */
	xor	dx,dx
	xor	cx,cx
	inc	cx
	cmp	al,5
	ja	Lkeyp		/* illegal */
	je	LbCHS		/* 5: floppy */
	xor	ebp,ebp
	cmp	al,4
	je	Lbjmp		/* 4: MBR */
	shl	al,4
	add	bl,al
	jmp	LbLBA		/* 0..3: partition */
#endif
Lscanp:	mov	al,[apart]
	cmp	al,3
	jbe	Lscan2
Lscan1:	cmp	byte ptr [bx],0x80
	je	LbLBA		/* active partition */
	add	bl,0x10
	cmp	bl,0xFE
	jb	Lscan1
	jmp	Lkeyp		/* not found */
Lscan2:	cbw
	shl	al,4
	add	bl,al
LbLBA:	mov	dx,[bx]
	mov	cx,[bx+2]
	mov	ebp,[bx+8]
Lbjmp:	mov	dl,0x80
	xor	si,si
	xor	di,di
	mov	ax,0x0010
	stosw
	xor	ax,ax
	inc	ax
	stosw
	mov	ax,0x7C00
	stosw
	xor	ax,ax
	stosw
	mov	eax,ebp
	stosd
	xor	eax,eax
	stosd
	mov	ah,0x42
	call	Ltry
LbCHS:	mov	ax,0x0201
	mov	bx,0x0200
	call	Ltry
#ifndef	BOOTMANAGER
Lkeyp:	/* only if not bootmanager code, this label here */
#endif
	call	Labend
	.asciz	"bad magic\r\n"
Labend:	pop	si
	call	Lotxt
	xor	ax,ax
	int	0x16
	jmp	0xF000,0xFFF0

	. = 0x01B7
apart:	.byte	0xFF

	. = 0x01B8
	/* some Microsoft® NT stuff */

	. = 0x01BE
	/* partition table */

	. = 0x01EE
	/* ABI for second-stage boot loader if used as PBR */
	.word	0, Lotxt, 0	/* offset 0x01F0 - Lotxt */
	.word	Ltry0		/* offset 0x01F4 - Ltry0 */
	.word	0xAA55 - Lotxt	/* offset 0x01F6 - magic */
#ifdef	BOOTMANAGER
	.word	Ltimeout	/* offset 0x01F8 - timeout, measured in ticks */
#else
	.word	0xFFFF		/* nothing (this is for fdisk btw) */
#endif
	/* free */		/* offset 0x01FA..0x01FD */

	. = 0x01FE
	.word	0xAA55		/* magic */
