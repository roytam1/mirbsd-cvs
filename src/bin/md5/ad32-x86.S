/* $MirOS: src/share/misc/licence.template,v 1.7 2006/04/09 22:08:49 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Copyright (C) 1995 Mark Adler
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
 */

#ifdef UNDERSCORES
#define	_C(x)	_ ## x
#else
#define	_C(x)	x
#endif

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

	.intel_syntax noprefix
	.section .comment
	.asciz	"$MirOS$"
	.text

/* void ADLER32_Update(ADLER32_CTX *ctx, const uint8_t *buf, size_t len) */
	.globl	_C(ADLER32_Update)
_C(ADLER32_Update):
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	push	edi
	mov	eax,[ebp+8]	/* ctx */
	mov	esi,[ebp+12]	/* buf */
	mov	ecx,[ebp+16]	/* len */

	mov	edi,[eax]	/* *ctx */
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
	or	edi,ebx
	mov	eax,[ebp+8]	/* ctx */
	mov	[eax],edi
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
