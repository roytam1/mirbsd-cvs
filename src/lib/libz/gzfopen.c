/* $MirOS: src/share/misc/licence.template,v 1.5 2006/01/24 12:48:21 tg Rel $ */

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

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include "zutil.h"

__RCSID("$MirOS$");

static int zf_read(void *, char *, int);
static int zf_write(void *, const char *, int);
static int zf_close(void *);

FILE *
gzfopen(const char *path, const char *mode)
{
	gzFile s;
	FILE *f;
	bool r;

	if (*mode == 'r')
		r = true;
	else if ((*mode == 'w') || (*mode == 'a'))
		r = false;
	else {
		errno = EINVAL;
		return (NULL);
	}

	s = gzopen(path, mode);
	if (s == (gzFile)Z_NULL) {
		errno = ENXIO;
		return (NULL);
	}

	if (s->file == NULL) {
		gzclose(s);
		errno = ENXIO;
		return (NULL);
	}

	if ((f = funopen((void *)s, r ? zf_read : NULL,
	    r ? NULL : zf_write, NULL, zf_close)) == NULL) {
		int e = errno;
		gzclose(s);
		errno = e;
		return (NULL);
	}

	return (f);
}
