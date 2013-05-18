/* $MirOS: src/bin/md5/suma-mi.c,v 1.3 2005/11/16 17:08:47 tg Exp $ */

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
#include <err.h>
#include <stdio.h>
#include "suma.h"

void
SUMA_Init(SUMA_CTX *ctx)
{
	if (ctx != NULL)
		*ctx = 0xFFFFFFFF;
}

void
SUMA_Update(SUMA_CTX *ctx __attribute__((unused)),
    const u_int8_t *data __attribute__((unused)),
    size_t len __attribute__((unused)))
{
	errx(1, "SUMA_Update not implemented");
}

void
SUMA_Final(SUMA_CTX *ctx __attribute__((unused)))
{
	errx(1, "SUMA_Final not implemented");
}
