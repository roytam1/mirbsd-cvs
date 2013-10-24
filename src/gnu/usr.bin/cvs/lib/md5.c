/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2005, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/types.h>
#include <stdlib.h>
#include "md5.h"

__RCSID("$MirOS: src/gnu/usr.bin/cvs/lib/md5.c,v 1.3 2005/12/05 22:12:45 tg Exp $");

char *
md5_buffer(const u_int8_t *buf, size_t buflen, char *hash)
{
	MD5_CTX ctx;

	if (hash == NULL)
		if ((hash = malloc(MD5_DIGEST_LENGTH)) == NULL)
			return NULL;

	MD5Init(&ctx);
	MD5Update(&ctx, buf, buflen);
	MD5Final((uint8_t *)hash, &ctx);

	return hash;
}