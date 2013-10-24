/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
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
 *-
 * Arcfour cipher re-implementation from (alledged) spec description.
 * Optimised key scheduling algorithm. Key length must equal 256.
 */

#include <libckern.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

void
arcfour_ksa256(struct arcfour_status *c, const uint8_t key[256])
{
	register uint8_t i, j, si, n = 0;

	i = c->i - 1;
	j = c->j;
	do {
		++i;
		si = c->S[i];
		j = (uint8_t)(j + si + key[n++]);
		c->S[i] = c->S[j];
		c->S[j] = si;
	} while (n);
	c->j = c->i = i + 1;
}