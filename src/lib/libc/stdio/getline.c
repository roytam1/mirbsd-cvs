/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__RCSID("$MirOS$");

ssize_t
getline(char **dst, size_t *siz, FILE *f)
{
	size_t n;
	char *buf;

	if ((dst == NULL) || (siz == NULL) || (f == NULL)) {
		errno = EINVAL;
		return (-1);
	}

	if ((buf = fgetln(f, &n)) == NULL)
		return (-1);	/* includes feof(f) */

	if ((*dst == NULL) || (*siz < n + 1)) {
		char *newdst;

		if ((newdst = realloc(*dst, n + 1)) == NULL)
			return (-1);
		*dst = newdst;
		*siz = n + 1;
	}

	memcpy(*dst, buf, n);
	(*dst)[n] = '\0';

	return (n);
}
