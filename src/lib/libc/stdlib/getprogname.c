/* $MirOS: src/lib/libc/stdlib/getprogname.c,v 1.3 2005/12/17 05:46:15 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <stdlib.h>
#include <string.h>

__RCSID("$MirOS: src/lib/libc/stdlib/getprogname.c,v 1.3 2005/12/17 05:46:15 tg Exp $");

extern char *__progname;

/*
 * Some other OSes actually use this, but for us,
 * the CSU is smart enough to set __progname.
 */
void
setprogname(const char *s)
{
	/* I'd just return here, but what if it's unset? */
	char *t;

	/* Don't reset if there's already a progname set */
	if (__predict_true(*__progname) || __predict_false(s == NULL))
		return;

	if ((t = strrchr(s, '/')) == NULL)
		__progname = strdup(s);
	else
		__progname = strdup(++t);
}

/*
 * This is... well.
 */
const char *
getprogname(void)
{
	return __progname;
}
