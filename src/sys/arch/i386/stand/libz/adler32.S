/* $MirOS: src/sys/arch/i386/stand/libz/adler32.S,v 1.2 2006/10/07 21:36:20 tg Exp $ */

/*-
 * Copyright (c) 2006
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
 *-
 * See also:
 *	contrib/hosted/fwcf/adler.h,v
 *	src/sys/arch/i386/stand/libz/adler32.S,v
 *	src/sys/lib/libsa/adler32s.c,v
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
	.asciz	"$MirOS: src/sys/arch/i386/stand/libz/adler32.S,v 1.2 2006/10/07 21:36:20 tg Exp $"
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
