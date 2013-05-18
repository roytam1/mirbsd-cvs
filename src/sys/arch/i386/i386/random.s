/* $MirOS: src/sys/arch/i386/i386/random.s,v 1.4 2007/09/28 18:33:24 tg Exp $ */

/*-
 * Copyright (c) 2001, 2003, 2004
 *	Thorsten Glaser <tg@mirbsd.de>
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
