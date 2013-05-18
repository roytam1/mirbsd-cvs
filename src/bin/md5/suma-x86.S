/* $MirOS: src/bin/md5/suma-x86.S,v 1.4 2005/12/17 05:46:05 tg Exp $ */

/*-
 * Copyright (c) 2005
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
 */

#ifdef UNDERSCORES
#define	_C(x)	_ ## x
#else
#define	_C(x)	x
#endif

	.intel_syntax noprefix
	.section .comment
	.asciz	"$MirOS: src/bin/md5/suma-x86.S,v 1.4 2005/12/17 05:46:05 tg Exp $"
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


/* void SUMA_Init(SUMA_CTX *ctx) */
	.globl	_C(SUMA_Init)
_C(SUMA_Init):
	mov	edx,[esp+4]
	xor	eax,eax
	dec	eax
	mov	[edx],eax
	ret


/* void SUMA_Update(SUMA_CTX *ctx, const uint8_t *data, size_t len) */
	.globl	_C(SUMA_Update)
_C(SUMA_Update):
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


/* void SUMA_Final(SUMA_CTX *ctx) */
	.globl	_C(SUMA_Final)
_C(SUMA_Final):
	mov	ecx,[esp+4]	/* ctx */
	push	ebx
	mov	edx,[ecx]
	xor	eax,eax
	UPDATE_ONE
	mov	[ecx],edx
	pop	ebx
	ret
