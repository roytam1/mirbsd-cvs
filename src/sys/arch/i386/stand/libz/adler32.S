/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * The adler32 algorithm is
 * Copyright (C) 1995 Mark Adler
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
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
	.asciz	"$MirOS: src/bin/md5/ad32-x86.S,v 1.1 2006/05/26 11:55:16 tg Exp $"
	.text

/* void ADLER32_Update(ADLER32_CTX *ctx, const uint8_t *buf, size_t len) */
/* u_long adler32(u_long adler, const uint8_t *buf, unsigned len) */
	.globl	_C(adler32)
_C(adler32):
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
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
