/*-
 * Copyright (c) 2008
 *	Thorsten Glaser <tg@mirbsd.org>
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
 */

#include <machine/asm.h>

RCSID("$MirOS$")

	.intel_syntax noprefix
	.text

NENTRY(strcoll)
ENTRY(strcmp)
	push	esi
	mov	esi,8[esp]
	mov	edx,12[esp]
	cld
	xor	eax,eax
	xor	ecx,ecx
	dec	edx

	.p2align 2,0x90
Lloop:	inc	edx
	lodsb
	or	al,al
	jz	Lend
	cmp	[edx],al
	jne	Lend
	inc	edx
	lodsb
	or	al,al
	jz	Lend
	cmp	[edx],al
	je	Lloop
	.p2align 2,0x90
Lend:	mov	cl,[edx]
	sub	eax,ecx
	pop	esi
	ret
