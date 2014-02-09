/*-
 * Copyright © 2014 Tomasz Konojacki
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 */

#define __STDC_WANT_LIB_EXT1__ 1

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

char *
gets_s(char *buf, rsize_t n)
{
	char *str = buf;
	int c = 0;
	bool discard = false;

	if (!buf || !n || (n > RSIZE_MAX))
		discard = true;

	while (discard || (n-- > 1)) {
		c = getchar();

		if ((c == EOF) || (c == '\n'))
			break;
		else if (!discard)
			*(str++) = c;
	}

	*str = 0;

	if (discard || ((c == EOF) && (str == buf)))
		buf = NULL;

	return (buf);
}
