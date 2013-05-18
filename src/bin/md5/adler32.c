/* $MirOS: src/bin/md5/adler32.c,v 1.1 2006/05/26 11:55:16 tg Exp $ */

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
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "adler32.h"

void
ADLER32_Init(ADLER32_CTX *ctx)
{
	if (ctx != NULL)
		*ctx = 1;
	/*	*ctx = adler32(0, NULL, 0); */
}

#ifndef USE_ASM
void
ADLER32_Update(ADLER32_CTX *ctx, const uint8_t *buf, size_t len)
{
	if (ctx == NULL)
		return;

	*ctx = adler32(*ctx, buf, len);
}
#endif

char *
ADLER32_End(ADLER32_CTX *ctx, char *res)
{
	if (res)
		snprintf(res, ADLER32_DIGEST_STRING_LENGTH, "%08X", *ctx);
	else if (asprintf(&res, "%08X", *ctx) == -1)
		res = NULL;

	return (res);
}

void
cksum_addpool(const char *x __attribute__((unused)))
{
#ifdef ZLIB_HAS_ADLERPUSH
	adler32(arc4random(), (const uint8_t *)x, strlen(x));
#endif
}
