/* From: $NetBSD: crti.c,v 1.2 2002/11/23 17:21:22 thorpej Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2013
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
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
 * the possibility of such damage or existence of a defect.
 */

/* this is safe because it's either in .comment or in .data and ld reorders */
#include <sys/cdefs.h>
__RCSID("$MirOS: src/lib/csu/common_elf/crti.c,v 1.7 2008/11/08 23:03:51 tg Exp $");

/*-
 * Mark all objects having a PT_NOTE section identifying
 * ourselves as MirOS BSD executables / (shared) objects
 *
 * The MirOS Project uses the "MirOS "+string marker for
 * checking the validity of the executables - currently,
 * the strings "MirOS Linux" and "MirOS BSD" are checked
 * for by the kernel. Traditionally, the "MirBSD" can be
 * used as an alias for "MirOS BSD", but this may change
 * in the future.
 * The "desc" for type 1 (OS version note) currently has
 * to be set to zero. Its least significant byte is used
 * as a version indicator; if it should ever be != zero,
 * the most significant byte in the first doubleword (32
 * bit) must be set to -1 (0xFF) for endianness reasons.
 * The two middle bytes, and all following bytes, can be
 * used as the version specifies.
 *
 * see also: http://www.netbsd.org/Documentation/kernel/elf-notes.html
 */

__asm__(".section .note.miros.ident,\"a\",@progbits"
"\n	.p2align 2"
"\n	.long	2f-1f"			/* name size */
"\n	.long	4f-3f"			/* desc size */
"\n	.long	1"			/* type (OS version note) */
"\n1:	.asciz	\"MirOS BSD\""		/* name */
"\n2:	.p2align 2"
"\n3:	.long	0"			/* desc */
"\n4:	.p2align 2");


/*-
 * Copyright (c) 1998, 2001, 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Paul Kranenburg, Ross Harvey, and Jason R. Thorpe.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/exec.h>
#include <sys/exec_elf.h>

#include "dot_init.h"

INIT_FALLTHRU_DECL;
FINI_FALLTHRU_DECL;

void _init(void) __attribute__((__section__(".init")));
void _fini(void) __attribute__((__section__(".fini")));

void
_init(void)
{
	INIT_FALLTHRU();
}

void
_fini(void)
{
	FINI_FALLTHRU();
}

MD_INIT_SECTION_PROLOGUE;
MD_FINI_SECTION_PROLOGUE;
