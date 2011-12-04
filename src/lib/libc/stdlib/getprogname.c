/* $MirOS: src/lib/libc/stdlib/getprogname.c,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $ */

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

#include <stdlib.h>
#include <string.h>

__RCSID("$MirOS: src/lib/libc/stdlib/getprogname.c,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $");

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
