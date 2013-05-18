/* $MirOS: src/share/misc/licence.template,v 1.7 2006/04/09 22:08:49 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <wchar.h>

__RCSID("$MirOS$");

int
mbtowc(wchar_t *__restrict__ pwc, const char *__restrict__ s, size_t n)
{
	mbstate_t state;
	int rv;

	if (s == NULL)
		return (0);

	bzero(&state, sizeof (mbstate_t));
	if ((rv = mbrtowc(pwc, s, n, &state)) < 0)
		return (-1);
	return (rv);
}
