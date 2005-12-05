/* $MirOS: src/gnu/usr.bin/cvs/lib/md5.c,v 1.2 2005/03/13 15:50:35 tg Exp $ */

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

#include <sys/types.h>
#include <stdlib.h>
#include "md5.h"

__RCSID("$MirOS: src/gnu/usr.bin/cvs/lib/md5.c,v 1.2 2005/03/13 15:50:35 tg Exp $");

char *
md5_buffer(const u_int8_t *buf, size_t buflen, char *hash)
{
	MD5_CTX ctx;

	if (hash == NULL)
		if ((hash = malloc(MD5_DIGEST_LENGTH)) == NULL)
			return NULL;

	MD5Init(&ctx);
	MD5Update(&ctx, buf, buflen);
	MD5Final(hash, &ctx);

	return hash;
}
