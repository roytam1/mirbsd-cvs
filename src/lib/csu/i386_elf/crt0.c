/* $MirOS: src/lib/csu/i386_elf/crt0.c,v 1.4 2007/02/06 01:35:27 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2007
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
 * Loosely based upon code written for The NetBSD® Project.
 */

#include "common.h"

__asm__(".text"
"\n	.intel_syntax noprefix"
"\n	.p2align 2"
"\n	.globl	__start"
"\n	.globl	_start"
"\n_start:"
"\n__start:"
#ifdef extra_paranoid
"\n	cld"			/* see setregs() in i386 machdep.c */
#endif
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

__RCSID("$MirOS: src/lib/csu/i386_elf/crt0.c,v 1.4 2007/02/06 01:35:27 tg Exp $");
