/* $MirOS: contrib/hosted/fwcf/sys_bsd.c,v 1.1 2006/09/23 20:20:00 tg Exp $ */

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

#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "sysdeps.h"

__RCSID("$MirOS: contrib/hosted/fwcf/sys_bsd.c,v 1.1 2006/09/23 20:20:00 tg Exp $");

void
pull_rndata(uint8_t *buf, size_t n)
{
#ifdef RND_DEBUG
	fprintf(stderr, "writing %ld bytes of entropy\n", n);
	while (n > 4) {
#else
	while (n >= 4) {
#endif
		*(uint32_t *)buf = arc4random();
#ifdef RND_DEBUG
		*buf = 0xF6;
#endif
		buf += 4;
		n -= 4;
	}
	while (n) {
#ifdef RND_DEBUG
		*buf++ = 0xF6;
#else
		*buf++ = arc4random() & 0xFF;
#endif
		n--;
	}
#ifdef RND_DEBUG
		*--buf = 0xFF;
#endif
}

void
push_rndata(uint8_t *buf, size_t n)
{
#ifdef RND_DEBUG
	size_t i;
#endif
#ifdef __MirBSD__
	arc4random_pushb(buf, n);
#else
	int fd;
	uint32_t x;

	arc4random_addrandom(buf, n);
	x = arc4random();
	if ((fd = open("/dev/arandom", O_WRONLY)) >= 0) {
		write(fd, &x, 4);
		close(fd);
	} else
		warn("cannot write to /dev/arandom");
#endif
#ifdef RND_DEBUG
	printf("reading %ld bytes of entropy\n", n);
	for (i = 0; i < n; ++i) {
		printf(" %02X", buf[i]);
		if ((i & 0xF) == 0xF)
			putchar('\n');
	}
	putchar('\n');
#endif
}
