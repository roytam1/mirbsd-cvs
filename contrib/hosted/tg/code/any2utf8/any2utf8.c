/* $MirOS: contrib/hosted/tg/code/any2utf8/wide.c,v 1.1 2009/08/02 17:12:07 tg Exp $ */

/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <t.glaser@tarent.de>
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

#include <err.h>
#include <errno.h>
//#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

extern size_t ucs_8to32(const char *src, unsigned int *dst);
extern size_t ucs_32to8(char *dst, unsigned int wc);

int
main(void)
{
	size_t n = 0, i;
	char *srcbuf = NULL;
	size_t srcsz = 0;
	unsigned int wc;
	char dstbuf[8];

 loop_incr:
	srcsz = srcsz ? srcsz << 1 : 4096;
	if ((srcbuf = realloc(srcbuf, srcsz)) == NULL)
		err(1, "realloc %zu bytes", srcsz);
 loop_read:
	if ((i = read(0, srcbuf + n, srcsz - n)) == 0)
		goto end_read;
	if (i == (size_t)-1) {
		if (errno == EINTR)
			goto loop_read;
		err(1, "read %zu bytes", srcsz - n);
	}
	n += i;
	goto loop_incr;

 end_read:
	srcsz = n + 1;
	if ((srcbuf = realloc(srcbuf, srcsz)) == NULL)
		err(1, "realloc %zu bytes", srcsz);
	srcbuf[--srcsz] = 0;

	i = 0;
	while (i < srcsz) {
		i += ucs_8to32(srcbuf + i, &wc);
		n = ucs_32to8(dstbuf, wc);
		if ((size_t)write(1, dstbuf, n) != n)
			err(1, "write %zu bytes", n);
	}

	return (0);
}
