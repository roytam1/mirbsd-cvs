/*-
 * Copyright (c) 2008, 2009, 2014
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

RCSID("$MirOS: src/kern/c/i386/memset.S,v 1.6 2009/01/21 19:57:54 tg Exp $")

	.intel_syntax noprefix
	.text

/* the kernel has sse_pagezero and friends */
#ifndef _KERNEL
ENTRY(bzero)
	mov	edx,8[esp]
	xor	eax,eax
	jmp	1f
#endif

ENTRY(memset)
	mov	edx,12[esp]

	movzx	eax,byte ptr 8[esp]
	mov	ah,al
	mov	ecx,eax
	shl	eax,16
	mov	ax,cx

1:	push	edi
	mov	edi,8[esp]
	push	edi
	cld

	/* do not align for short strings */
	cmp	edx,16
	jb	Lrest

	/* dword align */
	mov	ecx,edi
	neg	ecx
	and	ecx,3
	sub	edx,ecx
	rep	stosb

	/* fill whole dwords */
	mov	ecx,edx
	shr	ecx,2
	and	edx,3
	rep	stosd

	_ALIGN_TEXT
Lrest:	/* remaining bytes */
	mov	ecx,edx
	rep	stosb

	pop	eax
	pop	edi
	ret
