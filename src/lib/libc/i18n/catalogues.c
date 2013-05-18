/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
#include <locale.h>
#include <nl_types.h>

__RCSID("$MirOS: src/lib/libc/gen/i18n.c,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $");

/* fake NLS support */

nl_catd
_catopen(const char *name, int oflag)
{
	return (nl_catd) 0;
}

int
_catclose(nl_catd catd)
{
	return 0;
}

char *
_catgets(nl_catd catd, int set_id, int msg_id, const char *s)
{
	return (char *) s;
}

__weak_alias(catopen, _catopen);
__weak_alias(catclose, _catclose);
__weak_alias(catgets, _catgets);
