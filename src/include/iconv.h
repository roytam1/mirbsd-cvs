/* $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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
 * Expose standardised iconv(3) interface, implementation-independent
 */

#ifndef _ICONV_H_
#define _ICONV_H_

#include <sys/cdefs.h>
#include <machine/ansi.h>

#ifndef _ICONV_HAVE_ICONV_T
typedef void *iconv_t;
#endif

__BEGIN_DECLS
iconv_t iconv_open(const char *, const char *);
size_t iconv(iconv_t, char **__restrict__, size_t *__restrict__,
    char **__restrict__, size_t *__restrict__);
int iconv_close(iconv_t);
__END_DECLS

#endif
