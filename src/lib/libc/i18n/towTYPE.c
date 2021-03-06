/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2006
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

#include <wctype.h>

#define mir18n_caseconv
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/towTYPE.c,v 1.2 2006/11/01 20:01:19 tg Exp $ expanded to tow@@TYPE@@.c");

#undef tow@@TYPE@@
wint_t
tow@@TYPE@@(wint_t wc)
{
	return (towctrans(wc, to@@TYPE@@_table));
}
