/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2004, 2005
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
 * Loosely based upon code written for The NetBSD(tm) Project.
 */

#include "common.h"

__asm__(".text"
"\n	.intel_syntax noprefix"
"\n	.p2align 2"
"\n	.globl	__start"
"\n	.globl	_start"
"\n_start:"
"\n__start:"
"\n	push	ebx"		/* ps_strings	*/
"\n	push	ecx"		/* obj		*/
"\n	push	edx"		/* cleanup	*/
"\n	mov	eax,[esp+12]"
"\n	lea	ecx,[esp+4*eax+20]"
"\n	lea	edx,[esp+16]"
"\n	push	ecx"		/* envp		*/
"\n	push	edx"		/* argv		*/
"\n	push	eax"		/* argc		*/
"\n	call	___start"
"\n	.att_syntax");

#include "common.c"

__RCSID("$MirOS$");
