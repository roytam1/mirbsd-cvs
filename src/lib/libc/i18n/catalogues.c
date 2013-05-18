/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2005
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
 */

#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <nl_types.h>

__RCSID("$MirOS: src/lib/libc/i18n/catalogues.c,v 1.7 2006/11/01 20:01:18 tg Exp $");

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
