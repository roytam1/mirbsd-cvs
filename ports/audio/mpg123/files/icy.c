/*-
 * Copyright (c) 2008
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
 * Helpers for parsing the Shoutcast Metadata Protocol, formerly ICY,
 * together with a patch to httpget.c for appropriate HTTP headers.
 *
 * The following URIs are helpful for implementers of this standard:
 * - http://forums.radiotoolbox.com/viewtopic.php?t=74
 * - http://www.smackfu.com/stuff/programming/shoutcast.html
 */

#include <sys/types.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpg123.h"

__RCSID("$MirOS: ports/audio/mpg123/files/icy.c,v 1.1 2008/05/16 22:14:19 tg Exp $");

static int icy_freq, icy_done;
static char *icy_buf = NULL;

static int icy_parse(int);

int
icy_init(int freq)
{
	/* sanity check */
	if (freq < 0 || freq > 1024 * 1024 * 1024)
		freq = 0;

	icy_freq = freq;
	icy_done = 0;

	if (icy_buf) {
		free(icy_buf);
		icy_buf = NULL;
	}

	return (freq);
}

void
icy_close(int fd)
{
	if (icy_buf) {
		free(icy_buf);
		icy_buf = NULL;
	}
	icy_freq = 0;
	close(fd);
}

ssize_t
icy_read(int d, void *sbuf, size_t nbytes)
{
	ssize_t n, tot = 0;
	uint8_t *buf = sbuf;

	if (!icy_freq)
		return (read(d, sbuf, nbytes));

	while (nbytes) {
		size_t r;

		if (icy_done == icy_freq) {
			if (icy_parse(d))
				return (-1);
			icy_done = 0;
		}
		r = icy_freq - icy_done;
		if (r > nbytes)
			r = nbytes;
		n = read(d, buf, r);
		if (n < 0)
			return (n);
		tot += n;
		buf += n;
		nbytes -= n;
		icy_done += n;
	}

	return (tot);
}

static int
icy_parse(int fd)
{
	uint8_t nparas;
	char *newbuf;
	size_t blen;

	if (read(fd, &nparas, 1) != 1)
		return (-1);
	if (!nparas)
		return (0);
	if ((newbuf = malloc((blen = nparas * 16) + 1)) == NULL)
		return (-1);
	if ((size_t)read(fd, newbuf, blen) != blen)
		return (-1);
	newbuf[blen] = '\0';

	if (icy_buf == NULL) {
		putc('\n', stderr);
		goto usenew;
	} else if (strcmp(icy_buf, newbuf)) {
		free(icy_buf);
 usenew:
		icy_buf = newbuf;
		fprintf(stderr, "ICY metadata: %ls\n", uniprint(icy_buf));
	} else
		free(newbuf);
	return (0);
}
