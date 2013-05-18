/* $MirOS: src/lib/libc/i18n/isutf8.c,v 1.5 2005/12/17 05:46:14 tg Exp $ */

/*-
 * Copyright (c) 2005, 2006
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
 */

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/isutf8.c,v 1.5 2005/12/17 05:46:14 tg Exp $");

bool __locale_is_utf8 = false;

int __weak___mb_cur_max(void);

int
__weak___mb_cur_max(void)
{
	return (__locale_is_utf8 ? 3 : 1);
}

__weak_alias(__mb_cur_max, __weak___mb_cur_max);
