/* $MirOS: src/lib/libmbfun/mbfun.h,v 1.2 2011/07/17 17:20:20 tg Exp $ */

/*-
 * Copyright (c) 2010, 2011, 2013
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
 *-
 * Function declarations for libmbfun (MirBSD-local functions)
 */

#ifndef _MBFUN_H
#define _MBFUN_H

#include <syskern/libckern.h>

__BEGIN_DECLS
/* support routine for lseek+read to make 2048-byte aligned I/O */
ssize_t cdblockedread(int, void *, size_t, off_t)
    __attribute__((__bounded__(__buffer__, 2, 3)));
__END_DECLS

#endif
