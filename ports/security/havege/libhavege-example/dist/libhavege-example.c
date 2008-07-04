/* $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $ */

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
 */

#include <sys/param.h>
#include <err.h>
#include <fcntl.h>
#include <havege.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__RCSID("$MirOS$");

#if defined(__MirBSD__) && (MirBSD >= 0x0A80)
#define RANDOMNAME	"/dev/wrandom"
#else
#define RANDOMNAME	"/dev/urandom"
#endif

#define TOTAL		(16384 / sizeof (int))		/* integers */
#define FIRST		(4 * sizeof (int))		/* bytes */
#define REST		(sizeof (buf) - FIRST)		/* bytes */
int buf[TOTAL];

int
main(void)
{
	int fd, i;

	if ((fd = open(RANDOMNAME, O_WRONLY)) < 0)
		err(1, "cannot open %s", RANDOMNAME);

	for (;;) {
		for (i = 0; i < TOTAL; ++i)
			buf[i] = crypto_ndrand();
		if (write(fd, buf, FIRST) != FIRST)
			err(1, "could not write to %s", RANDOMNAME);
		if (write(STDOUT_FILENO, &buf[4], REST) != REST)
			err(1, "could not write to %s", "standard output");
		if (usleep(62500))
			err(1, "could not sleep for 62.5ms");
	}

	return (0);
}
