/* $MirOS: src/lib/libc/arch/i386/string/memmove.S,v 1.3 2005/04/17 03:05:44 tg Exp $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <machine/asm.h>

RCSID("$MirOS: src/lib/libc/arch/i386/string/memmove.S,v 1.3 2005/04/17 03:05:44 tg Exp $")
WARN_REFERENCES(bcopy, \
    "warning: bcopy(s,d,l) is deprecated, consider using memmove(d,s,l)")

	.intel_syntax noprefix
	.text

ENTRY(bcopy)
	push	esi
	push	edi
	mov	esi,12[esp]
	mov	edi,16[esp]
	jmp	move

NENTRY(memcpy)
ENTRY(memmove)
	push	esi
	push	edi
	mov	edi,12[esp]
	mov	esi,16[esp]
move:	mov	ecx,20[esp]
	push	edi
	mov	edx,ecx
	/* check for overlap / null op */
	jecxz	null
	cmp	esi,edi
	jb	bkwd
	je	null
	/* copy forwards, source > dest */
	cld
	/* first, whole dwords */
	shr	ecx,2
	rep
	movsd
	/* then, 0-3 remaining bytes */
	mov	cl,dl
	and	cl,3
	rep
	movsb
	pop	eax
	pop	edi
	pop	esi
	ret
bkwd:	/* copy backwards, source < dest */
	std
	/* start at the end */
	add	esi,ecx
	dec	esi
	dec	esi
	dec	esi
	dec	esi
	add	edi,ecx
	dec	edi
	dec	edi
	dec	edi
	dec	edi
	/* first, whole dwords */
	shr	ecx,2
	rep
	movsd
	/* then, 0-3 remaining bytes */
	inc	esi
	inc	esi
	inc	esi
	inc	edi
	inc	edi
	inc	edi
	mov	cl,dl
	and	cl,3
	rep
	movsb
	/* clean up */
null:	pop	eax
	pop	edi
	pop	esi
	cld
	ret
