/*-
 * Copyright (c) 2005, 2007
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

#ifdef _LIBMIRMAKE
#ifndef _ALIGN_TEXT
#define _ALIGN_TEXT		.p2align 2, 0x90
#endif
#define FTYPE(x)		.type x,@function
#define	_ENTRY(name) \
	.text; _ALIGN_TEXT; .globl name; FTYPE(name); name:
#define _PROF_PROLOGUE		/* no profiling */
#define ENTRY(name)		_ENTRY(_C_LABEL(name)); _PROF_PROLOGUE
#define RCSID(x)		.section .comment;		\
				.ascii "@(""#)rcsid: ";		\
				.asciz x;			\
				.previous
#else
#include <machine/asm.h>
#endif

RCSID("$MirOS: src/lib/libc/hash/suma-i386.S,v 1.1 2007/05/07 15:21:18 tg Exp $")

	.intel_syntax noprefix
	.text

/*
 * EAX: in data
 * EDX: in out CRC
 * EBX: BL clobbered
 */
#define	UPDATE_ONE				  \
	mov	bl,32				; \
8:	rcl	eax,1				; \
	rcl	edx,1				; \
	jnc	9f				; \
	xor	edx,0x04563521			; \
9:	dec	bl				; \
	jnz	8b


/* void SUMAInit(SUMA_CTX *ctx) */
ENTRY(SUMAInit)
	mov	edx,[esp+4]
	xor	eax,eax
	dec	eax
	mov	[edx],eax
	ret


/* void SUMAUpdate(SUMA_CTX *ctx, const uint8_t *data, size_t len) */
ENTRY(SUMAUpdate)
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	mov	eax,[ebp+8]	/* ctx */
	mov	esi,[ebp+12]	/* data */
	mov	ecx,[ebp+16]	/* len */
	jecxz	7f
	mov	edx,[eax]
	cld
	push	ecx
	shr	ecx,2
	jecxz	2f
1:	lodsd
	UPDATE_ONE
	dec	ecx
	jnz	1b
2:	pop	ecx
	and	cl,3
	jz	6f
	xor	eax,eax
	lodsb
	dec	cl
	je	3f
	ror	eax,8
	lodsb
	rol	eax,8
	dec	cl
	je	3f
	ror	eax,16
	lodsb
	rol	eax,16
3:	UPDATE_ONE
6:	mov	eax,[ebp+8]	/* ctx */
	mov	[eax],edx
7:	pop	esi
	pop	ebx
	pop	ebp
	ret


/* void SUMAPad(SUMA_CTX *ctx) */
ENTRY(SUMAPad)
	mov	ecx,[esp+4]	/* ctx */
	push	ebx
	mov	edx,[ecx]
	xor	eax,eax
	UPDATE_ONE
	mov	[ecx],edx
	pop	ebx
	ret


/* void SUMAFinal(uint8_t *dst, SUMA_CTX *ctx) */
ENTRY(SUMAFinal)
	mov	ecx,[esp+8]	/* ctx */
	push	ebx
	mov	edx,[ecx]
	xor	eax,eax
	UPDATE_ONE
	pop	ebx
	xor	eax,eax
	mov	[ecx],eax
	mov	ecx,[esp+4]	/* dst */
	bswap	edx
	mov	[ecx],edx
	ret
