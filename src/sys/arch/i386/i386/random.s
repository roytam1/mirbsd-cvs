/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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
