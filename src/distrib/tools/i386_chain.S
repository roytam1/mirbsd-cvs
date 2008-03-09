/* $MirOS: src/distrib/tools/i386_chain.S,v 1.6 2007/10/20 22:01:31 tg Exp $ */

/*-
 * Copyright (c) 2007
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

#ifndef CHAINSECTOR
#define CHAINSECTOR	24	/* first = sector 0 = CHS 0/0/1 */
#endif

	.intel_syntax noprefix
	.code16
	.text

GTENTRY(_start)
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
	/* transfer code and data there from 0x07C00 first */
	xor	di,di
	mov	si,0x0200
	mov	cx,0x0200 / 4
	rep	movsd
	/* jump to 'cs:offset Lmain' */
	lret

LTENTRY(Lmain)
	mov	ax,0x0201
	mov	bx,0x0200
/*	mov	cx,CHAINSECTOR + 1 */
	.byte	0xB9
GTENTRY(patch_sector)
	.word	CHAINSECTOR + 1
	mov	dh,0
Lload:	pusha
	int	0x13
	popa
	jnc	Lboot
	pusha
	xor	ax,ax
	int	0x13
	popa
	jmp	Lload
Lboot:	ljmp	0x0000,0x7C00
GTENTRY(pad_start)
#if 0
	nop

	.balign	4, 0x90
	.org	128 - 4
	.byte	0x90, 0x90, 0x55, 0xAA
#endif
