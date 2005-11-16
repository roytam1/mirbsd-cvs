/* $MirOS: contrib/code/mpczar/minizip/minizip.c,v 1.1 2005/11/16 20:29:41 tg Exp $ */

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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "zopen.h"

__RCSID("$MirOS: contrib/code/mpczar/minizip/minizip.c,v 1.1 2005/11/16 20:29:41 tg Exp $");

#undef BUFSIZ
#define BUFSIZ	256

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
		errx(1, "opening output file");
	}

	if ((outf = zdopen(fd, "w", 0)) == NULL)
		errx(1, "opening compressed output stream");

loop:
	n = read(STDIN_FILENO, buf, BUFSIZ);

	if (n < 0)
		errx(1, "reading input stream");
	if (n == 0)
		goto eof;

	if (!fwrite(buf, n, 1, outf))
		errx(1, "writing to output file");

	/* if (n != BUFSIZ) may fail in pipe situations */
	goto loop;

eof:
	if (fclose(outf))
		errx(1, "closing compressed output file");

	return (0);
}
