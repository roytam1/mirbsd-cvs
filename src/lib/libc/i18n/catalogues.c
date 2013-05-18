/* $MirOS: src/lib/libc/i18n/catalogues.c,v 1.6 2006/05/30 20:28:17 tg Exp $ */

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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <nl_types.h>

__RCSID("$MirOS: src/lib/libc/i18n/catalogues.c,v 1.6 2006/05/30 20:28:17 tg Exp $");

/* fake NLS support */

nl_catd _catopen(const char *, int);
/* const because of gcc warnings */
const char *_catgets(nl_catd, int, int, const char *);
int _catclose(nl_catd);

nl_catd
_catopen(const char *name __attribute__((unused)),
    int oflag __attribute__((unused)))
{
	return (0);
}

int
_catclose(nl_catd catd __attribute__((unused)))
{
	return (0);
}

const char *
_catgets(nl_catd catd __attribute__((unused)),
    int set_id __attribute__((unused)),
    int msg_id __attribute__((unused)),
    const char *s)
{
	return (s);
}

__weak_alias(catopen, _catopen);
__weak_alias(catclose, _catclose);
__weak_alias(catgets, _catgets);
