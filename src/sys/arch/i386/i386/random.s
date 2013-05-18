/* $MirOS: src/sys/arch/i386/i386/random.s,v 1.2 2005/03/06 21:26:58 tg Exp $ */

/*-
 * Copyright (c) 2001, 2003, 2004
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
 * Fast pseudo random number generator (rewritten from scratch). The
 * original is claimed to be from "Two Fast Implementations of the
 * 'Minimal Standard' Random Number Generator", David G. Carta, CACM
 * Jan 1990, Vol. 33 No. 1.
 * Don't modify this code unless you understand what you're doing AND
 * make sure its 10'000th invocation returns 1043618065 after the change.
 *
 * The result lies within ]0;2^31[  (i.e. is always a signed int32_t).
 */

#include <machine/asm.h>

	.intel_syntax noprefix

	.data
	.globl	_C_LABEL(_randseed)
_C_LABEL(_randseed):
	.long	0x00000001

	.text
ENTRY(random)
	mov	eax,[_C_LABEL(_randseed)]
	mov	edx,16807
	imul	edx
	shld	edx,eax,1
	mov	ecx,0x7FFFFFFF
	and	eax,ecx
	add	eax,edx
	jns	.fits
	sub	eax,ecx
.fits:	mov	[_C_LABEL(_randseed)],eax
	ret
