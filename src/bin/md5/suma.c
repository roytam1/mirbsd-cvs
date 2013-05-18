/* $MirOS: src/bin/md5/suma.c,v 1.2 2005/12/17 05:46:05 tg Exp $ */

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
#include "suma.h"

char *
SUMA_End(SUMA_CTX *ctx, char *res)
{
	SUMA_Final(ctx);

	if (res)
		snprintf(res, SUMA_DIGEST_STRING_LENGTH, "%08X", *ctx);
	else if (asprintf(&res, "%08X", *ctx) == -1)
		res = NULL;

	return (res);
}
