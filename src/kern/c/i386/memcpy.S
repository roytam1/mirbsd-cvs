/*-
 * Copyright (c) 2005, 2008
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

RCSID("$MirOS: src/kern/c/i386/memcpy.S,v 1.1 2008/08/03 21:02:02 tg Exp $")

	.intel_syntax noprefix
	.text

#ifndef L_mempcpy
ENTRY(bcopy)
	push	esi
	push	edi
	mov	esi,12[esp]
	mov	edi,16[esp]
	jmp	Lmove

NENTRY(memcpy)
ENTRY(memmove)
#else
ENTRY(mempcpy)
#endif
	push	esi
	push	edi
	mov	edi,12[esp]
	mov	esi,16[esp]
#ifndef L_mempcpy
	_ALIGN_TEXT
#endif
Lmove:	mov	ecx,20[esp]
	/* check for overlap / null op */
	jecxz	Lnull
	/* check if src == dst */
	cmp	esi,edi
	je	Lnull
#ifndef L_mempcpy
	push	edi
#endif
	mov	edx,ecx
	jb	Lbkwd	/* CF set from cmp esi,edi */
	/* copy forwards, source > dest */
	cld
	/* first, whole dwords */
	shr	ecx,2
	rep	movsd
	/* then, 0-3 remaining bytes */
	mov	cl,dl
	and	cl,3
	rep	movsb
#ifndef L_mempcpy
	pop	eax
	pop	edi
	pop	esi
	ret
#endif

Lnull:	mov	eax,edi
	pop	edi
	pop	esi
	ret

	_ALIGN_TEXT
Lbkwd:	/* copy backwards, source < dest */
	std
	/* start at the end */
	add	esi,ecx
	add	edi,ecx
#ifdef L_mempcpy
	push	edi
#endif
	/* fractional bytes first, whole dwords last */
	and	ecx,3
	dec	esi
	dec	edi
	rep	movsb
	mov	ecx,edx
	shr	ecx,2
	dec	esi
	dec	esi
	dec	esi
	dec	edi
	dec	edi
	dec	edi
	rep	movsd
	/* clean up */
	pop	eax
	pop	edi
	pop	esi
	cld
	ret
