/* $MirOS: src/bin/md5/suma-mi.c,v 1.1 2005/04/12 19:50:22 tg Exp $ */

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
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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
SUMA_Update(SUMA_CTX *ctx, const u_int8_t *data, size_t len)
{
	errx(1, "SUMA_Update not implemented");
}

void
SUMA_Final(SUMA_CTX *ctx)
{
	errx(1, "SUMA_Final not implemented");
}
