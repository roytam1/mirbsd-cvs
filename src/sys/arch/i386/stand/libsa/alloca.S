/* $MirOS: src/sys/arch/i386/stand/libsa/alloca.S,v 1.2 2005/03/06 21:27:05 tg Exp $ */

/*-
 * Copyright (c) 2003
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * allocates memory, just with automatic free in return (by stack)
 */

#include <machine/asm.h>

	.intel_syntax noprefix
	.text
ENTRY(alloca)
	pop	edx		/* return address */
	pop	eax		/* size to allocate */
	mov	ecx,esp		/* old frame pointer */
	add	eax,3
	and	eax,0xFFFFFFFC	/* round to next doubleword */
	sub	esp,eax
	mov	eax,esp		/* pointer to allocated space */
	push	dword ptr [ecx+12]
	push	dword ptr [ecx+8]
	push	dword ptr [ecx+4]
	push	dword ptr [ecx]	/* possibly saved stuff */
	push	eax		/* dummy */
	jmp	edx		/* return */
