/*-
 * Copyright (c) 2005
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "zopen.h"

__RCSID("$MirOS: contrib/code/mpczar/minizip/minizip.c,v 1.6 2006/11/19 12:44:59 tg Exp $");

#undef BUFSIZ
#define BUFSIZ	4096

char buf[BUFSIZ];

int
main(int argc, char *argv[])
{
	FILE *outf;
	int fd = STDOUT_FILENO;
	ssize_t n;

	if ((argc > 1) && strcmp(argv[1], "-"))
		fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd == -1) {
		while (read(STDIN_FILENO, buf, BUFSIZ) > 0)
			;
		err(1, "opening output file");
	}

	if ((outf = zdopen(fd, "w", 0)) == NULL)
		err(1, "opening compressed output stream");

	fd = 1;
 loop:
	n = read(STDIN_FILENO, buf, BUFSIZ);

	if (n < 0)
		err(1, "reading input stream");
	if (n == 0)
		goto eof;
	fd = 0;

	if (!fwrite(buf, n, 1, outf))
		err(1, "writing to output file");

	/* if (n != BUFSIZ) may fail in pipe situations */
	goto loop;

 eof:
	if (fclose(outf))
		err(1, "closing compressed output file");

	return (fd);
}
