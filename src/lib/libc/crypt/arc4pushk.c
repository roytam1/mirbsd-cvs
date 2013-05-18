/*-
 * Copyright (c) 2008
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

#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/taitime.h>
#include <stdlib.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $");

uint32_t
arc4random_pushk(const void *buf, size_t len)
{
	uint32_t res;
	size_t rlen;
	union {
		uint8_t buf[256];
		tai64na_t tai64tm;
		uint32_t xbuf;
	} idat;
	const uint8_t *cbuf = (const uint8_t *)buf;
	int mib[2];

	taina_time(&idat.tai64tm);
	for (rlen = 0; rlen < len; ++rlen)
		idat.buf[rlen % 256] ^= cbuf[rlen];
	len = MIN(256, len);

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	rlen = sizeof (res);
	res ^= idat.xbuf;

	sysctl(mib, 2, &res, &rlen, &idat.buf[0], len);

	return (res);
}
