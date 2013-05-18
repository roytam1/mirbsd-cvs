/* $MirOS: src/sys/arch/i386/stand/mbr/mbr.S,v 1.1 2007/02/26 00:13:27 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2007
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

	.intel_syntax noprefix
	.code16
	.text

ALTENTRY(_start)
	xor	eax,eax
	push	eax
	popfd
	/* set up stack from 07A0:FFFC (0x179FC) down */
	add	ax,0x07A0
	mov	ss,ax
	mov	sp,0xFFFC
	sti
	push	ax		/* for retf */
	push	offset Lmain
	/* set up code and data at 07A0:0000 (0x07A00) = 0000:7A00 up */
	mov	ds,ax
	mov	es,ax
	/* move ourselves just below 0x07C00 target load address */
	mov	si,0x0200
	xor	di,di
	mov	cx,si
	rep	movsb
	/* jump to 'cs:offset Lmain' */
	lret

	/* entry message */
DENTRY(Lmsg)
	.ascii	"Mir-" __BOOT_VER
#ifdef BOOTMANAGER
	/* Lm<nn> are patch points */
	.ascii	": 0="
DENTRY(Lm00)
	.ascii	"00 1="
DENTRY(Lm01)
	.ascii	"00 2="
DENTRY(Lm02)
	.ascii	"00 3="
DENTRY(Lm03)
	.ascii	"00 4=MBR 5=fdd CR=deflt\r\n"
#endif
	.asciz	">"

	/* message that we cannot boot correctly */
DENTRY(Lmsgf)
	.asciz	"bad magic\r\n"

	/* output NUL-terminated string from ds:si */
Lotxt0:	mov	ah,0x0E
	mov	bx,7
	int	0x10
Lotxt:	lodsb
	or	al,al
	jnz	Lotxt0
	ret

Lmain:	mov	si,offset Lmsg
#ifdef BOOTMANAGER
	/* patch the partition type values into the message */
	mov	di,offset Lm00
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
	call	LpBY
#endif
	call	Lotxt
	mov	bx,offset Lptab	/* we boot "this one" */
#ifdef BOOTMANAGER
	/* selection code */
	xor	ax,ax		/* read CMOS clock ticks since midnight */
	int	0x1A		/* 32-bit result in cx:dx */
	mov	di,cx		/* save it in edi for later */
	shl	edi,16
	mov	di,dx		/* 32-bit result in edi */
	add	edi,183		/* 10 seconds, rounded up one tick */
	.type	Ltimeout, @object
	.size	Ltimeout, 4
	Ltimeout = . - 4	/* offset of the "183" above */
Lilp:	mov	ah,1		/* check if key was was pressed */
	int	0x16
	jnz	Lkeyp		/* yep */
	/* delay loop */
	xor	ax,ax
	int	0x1A
	shl	ecx,16
	mov	cx,dx
	or	al,al		/* past midnight? */
	jz	Lsday		/* no */
	add	ecx,1573040	/* should be 1572480, but according to RBIL… */
Lsday:	cmp	ecx,edi		/* time is over? */
	ja	Lscanp		/* yes, fake a return keypress */
	jmp	Lilp		/* no, jump back to the input */
	/* below: input loop without timeout */
Lkeyp:	xor	ah,ah		/* get pressed key */
	int	0x16
	sub	al,13		/* return */
	jb	Lkeyp		/* illegal */
	je	Lscanp
	sub	al,0x30-13	/* '0' */
	jb	Lkeyp		/* illegal */
	xor	ebp,ebp		/* LBA offset '0' */
	xor	dx,dx		/* CHS values 0/0/1 */
	xor	cx,cx
	inc	cx
	cmp	al,5
	ja	Lkeyp		/* illegal */
	je	LbCHS		/* 5: floppy */
	cmp	al,4
	je	Lbjmp		/* 4: MBR */
	shl	al,4
	add	bl,al
	jmp	LbLBA		/* 0..3: partition */
Lscanp:	/* "return" */
#else
#define Lkeyp	Labend
#endif
	/* scan the partition table for an active partition */
	mov	al,[apart]	/* first: hard-coded by fdisk(8) 'fdef' */
	cmp	al,3		/* 0..3 are valid */
	jbe	Lscan2		/* got one */
Lscan1:	/* iterate over partition table entries */
	cmp	byte ptr [bx],0x80
	je	LbLBA		/* found an active partition */
	add	bl,0x10
	cmp	bl,0xFE
	jb	Lscan1		/* repeat for 4 partitions */
	jmp	Lkeyp		/* no active partition found */
Lscan2:	shl	al,4		/* partition table number (0..3) -> offset */
	add	bl,al
	/* try to boot (LBA first, then CHS) */
LbLBA:	mov	dx,[bx]		/* 0x01BE .. 0x01BF -> CHS values, part 1 */
	mov	cx,[bx+2]	/* 0x01C0 .. 0x01C1 -> CHS values, part 2 */
	mov	ebp,[bx+8]	/* 0x01C6 .. 0x01C9 -> LBA value "start" */
Lbjmp:	/* got LBA values in ebp, CHS values in cx:dx */
	mov	dl,0x80
	xor	si,si
	xor	di,di		/* LBA parm blk overwrites begin of code */
	mov	ax,0x0010
	stosw			/* word: pblk size 0x0010 bytes */
	mov	al,1
	stosw			/* word: # of sectors = 0x0001 */
	mov	ax,0x7C00
	stosw			/* word: dst offset */
	xor	ax,ax
	stosw			/* word: dst segment */
	mov	eax,ebp
	stosd
	xor	ax,ax
	stosw
	stosw			/* qword: LBA offset of start sector */
	/* do we really have LBA functions? */
	pusha
	mov	ah,0x41		/* LBA installation check */
	mov	bx,0x55AA	/* magic */
	int	0x13
	jc	LbCHS		/* CF set -> nope, use CHS */
	cmp	bx,0xAA55	/* magic */
	jne	LbCHS		/* bad magic -> nope, use CHS */
	and	cl,1		/* API subset support bitmap */
	jz	LbCHS		/* extended disc access funcs unsupported */
	popa
	/* try to load it using LBA */
	mov	ah,0x42		/* LBA extended read */
	call	Ltry		/* try to boot that */
	/* didn't work, try CHS next */
LbCHS:	mov	ax,0x0201	/* load 0x01 sector */
	mov	bx,0x0200	/* to ES:0200 = 0x07C00 */
	call	Ltry
Labend:	/* we can't boot, abort */
	mov	si,offset Lmsgf
	call	Lotxt
	xor	ax,ax		/* wait for any keypress */
	int	0x16
	jmp	0xF000,0xFFF0	/* reset */

Ltry:	mov	bp,4		/* number of tries */
	mov	ds:[0x3FE],bp	/* place where later should be 0x55AA magic */
Ltry0:	pusha
	int	0x13
	popa
	jc	Ltry9		/* error? again. */
	cmp	word ptr ds:[0x3FE],0x55AA
	jne	Ltry9		/* bad magic? again. */
	mov	ax,0x0E0D	/* output a carriage return */
	xor	bx,bx
	push	bx
	push	word ptr 0x7C00	/* retf address */
	push	dx		/* drive we loaded from */
	int	0x10
	pop	dx
	cli			/* be nice :) */
	lret			/* jump to 0000:7C00 */
Ltry9:	pusha
	xor	ax,ax		/* reset drive */
	int	0x13
	popa
	dec	bp
	jnz	Ltry0		/* retry */
	ret

#ifdef BOOTMANAGER
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

	. = 0x01B7
	.size	apart, 1
DENTRY(apart)
	.byte	0xFF		/* default partition [0..3] or none */

	. = 0x01B8
	/* Microsoft® NT volume ID, or so I think */

	. = 0x01BE
DENTRY(Lptab)
	/* partition table */

	. = 0x01F8
	/* this is pre-installation only */
	.size	L___hint, 2
DENTRY(L___hint)
#ifdef	BOOTMANAGER
	.word	Ltimeout	/* timeout, measured in ticks, for fdisk */
#else
	.word	0xFFFF
#endif
DENTRY(L___rest)

	. = 0x01FE
	.size	L___magic, 2
DENTRY(L___magic)
	.word	0xAA55
