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
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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
#include <errno.h>

__RCSID("$MirOS: src/lib/libc/i18n/towctrans.c,v 1.3 2007/02/02 19:28:34 tg Exp $");

wint_t
towctrans(wint_t wc, wctrans_t charmap)
{
	if (__predict_false(wc > WCHAR_MAX))
		return (wc);

	if (__predict_false(charmap == NULL)) {
		errno = EINVAL;
		return (wc);
	}

	return (wc + charmap[wc >> 8][wc & 0xFF]);
}
