/*-
 * Copyright © 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 2010
 *	Benny Siegert <bsiegert@gmx.de>
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
#include "lib.h"
#include "check.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/check/main.c,v 1.1 2010/03/09 19:38:48 bsiegert Exp $");

static char Options[] = "hm:q?";

bool Quiet = false;
char *ChkPattern = NULL;

static __dead void usage(void);

int
main(int argc, char **argv)
{
	int ch, rv;

	while ((ch = getopt(argc, argv, Options)) != -1)
		switch(ch) {
		case 'm':
			ChkPattern = optarg;
			break;
		case 'q':
			Quiet = true;
			break;
		case 'h':
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}

	argc -= optind;
	argv += optind;

	if (!argc)
		usage();

	if (ChkPattern)
		rv = check_pattern(ChkPattern, argc, argv);
	else {
		if (argc != 3)
			usage();
		rv = version_compare(argv[0], argv[1], argv[2]);
	}
	return rv;
}

static __dead void
usage(void)
{
    fprintf(stderr, "usage: %s\nusage: %s\n",
	"pkg_check version1 op version2",
	"pkg_info [-q] -m pattern pkgspec ...");
    exit(1);
}

void
cleanup(int sig __attribute__((__unused__)))
{
}
