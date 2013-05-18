/*-
 * Copyright (c) 2006, 2007, 2008
 *	Thorsten Glaser <tg@mirbsd.de>
 * The adler32 algorithm is
 * Copyright (C) 1995 Mark Adler
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
 *-
 * See also:
 *	contrib/hosted/fwcf/adler.h
 *	src/lib/libc/hash/adh32.c
 *	src/kern/z/adler32s.c
 *	src/kern/z/adler32_i386.S
 */

#include <machine/asm.h>
#ifdef _KERNEL
#include <dev/rndvar.h>
#endif

RCSID("$MirOS: src/kern/z/adler32_i386.S,v 1.11 2008/08/01 13:46:08 tg Exp $")

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

	.intel_syntax noprefix
	.text

/* void ADLER32_Update(ADLER32_CTX *ctx, const uint8_t *buf, size_t len) */
/* u_long adler32(u_long adler, const uint8_t *buf, unsigned len) */
ENTRY(adler32)
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	push	edi
	mov	edi,[ebp+8]	/* adler */
	mov	esi,[ebp+12]	/* buf */
	mov	ecx,[ebp+16]	/* len */

	xor	ebx,ebx
	mov	bx,di		/* EBX = s1 (lower half) */
	shr	edi,16		/* EDI = s2 (upper half) */

	cld
.L1:	jecxz	.L4
	mov	edx,NMAX
	cmp	ecx,edx
	jae	.L2
	mov	edx,ecx
.L2:	sub	ecx,edx
	/* do at most NMAX bytes at a time */
	xor	eax,eax
.L3:	lodsb
	add	ebx,eax
	add	edi,ebx
	dec	edx
	jnz	.L3
	/* s{1,2} %= BASE; */
	push	ebp
	mov	ebp,BASE
	/* EDX is already 0, cool */
	xor	eax,eax
	xchg	eax,ebx
	div	ebp
	xchg	ebx,edx
	/* EDX is 0 again, cool */
	mov	eax,edi
	div	ebp
	mov	edi,edx
	pop	ebp
	/* and loop */
	jmp	.L1
.L4:	/* return */
	shl	edi,16
	lea	eax,[edi+ebx]
#if defined(_KERNEL) || !defined(_STANDALONE)
	push	eax			/* return value */
	lea	eax,[esp]		/* == function argument */
	push	4			/* size */
	push	eax			/* address */
#ifdef _KERNEL
	call	rnd_lopool_add
#else
	call	arc4random_pushb_fast
#endif
	pop	eax			/* dummy */
	pop	eax			/* dummy */
	pop	eax			/* return value */
#endif
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
