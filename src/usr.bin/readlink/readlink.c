/* $MirOS: src/usr.bin/readlink/readlink.c,v 1.4 2005/12/17 05:46:29 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@MirBSD.org>
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

#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/usr.bin/readlink/readlink.c,v 1.4 2005/12/17 05:46:29 tg Exp $");

int main(int, char **);
__dead void usage(void);

int
main(int argc, char *argv[])
{
	char buf[PATH_MAX];
	int ch, nflag = 0, fflag = 0;
	size_t i;

	while ((ch = getopt(argc, argv, "fn")) != -1)
		switch (ch) {
		case 'f':
			fflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if ((i = strlen(argv[0])) > (PATH_MAX - 1))
		errx(1, "filename too long, max %d", PATH_MAX - 1);

	if (fflag) {
		if (realpath(argv[0], buf) == NULL)
			err(1, "realpath");
	} else {
		i = readlink(argv[0], buf, sizeof (buf) - 1);
		if ((ssize_t)i < 0)
			err(1, "readlink");
		buf[i] = '\0';
	}

	printf("%s%s", buf, nflag ? "" : "\n");
	return (0);
}

__dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s [-fn] pathname\n", __progname);
	exit(1);
}
