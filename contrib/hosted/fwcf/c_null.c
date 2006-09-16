/* $MirOS: contrib/hosted/fwcf/fts_subs.c,v 1.1 2006/09/15 21:11:23 tg Exp $ */

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

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/fts_subs.c,v 1.1 2006/09/15 21:11:23 tg Exp $");

static void c_null_load(void) __attribute__((constructor));
static int c_init(void);
static int c_compress(void **, void *, size_t)
    __attribute__((bounded (string, 2, 3)));

static fwcf_compressor c_null = {
	c_init,			/* init */
	c_compress,		/* compress */
	c_compress,		/* decompress */
	"null",			/* name */
	0			/* code */
};

static void
c_null_load(void)
{
	if (compress_register(&c_null))
		fputs("warning: cannot register compressor 'null'!\n", stderr);
}

static int
c_init(void)
{
	return (0);
}

static int
c_compress(void **dst, void *src, size_t len)
{
	if (dst == NULL)
		return (-1);
	if ((*dst = malloc(len)) == NULL)
		return (-1);
	memcpy(*dst, src, len);
	return (len);
}
