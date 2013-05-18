/* $MirOS: src/lib/libc/i18n/catalogues.c,v 1.3 2005/09/30 21:45:26 tg Exp $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <nl_types.h>

__RCSID("$MirOS: src/lib/libc/i18n/catalogues.c,v 1.3 2005/09/30 21:45:26 tg Exp $");

/* fake NLS support */

nl_catd _catopen(const char *, int);
/* const because of gcc warnings */
const char *_catgets(nl_catd, int, int, const char *);
int _catclose(nl_catd);

nl_catd
_catopen(const char *name __attribute__((unused)),
    int oflag __attribute__((unused)))
{
	return ((nl_catd) 0);
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
