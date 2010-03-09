/* $MirOS$
 *-
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

__RCSID("$MirOS$");

int
check_pattern(char *pattern, int argc, char **argv)
{
	int i, found = 0;
	char **pkg;

	for (i = 0, pkg = argv; i < argc; i++, pkg++) {
		if (pmatch(pattern, *pkg)) {
			found++;
			if (!Quiet)
				printf("%s\n", *pkg);
		}
	}

	return !found;
}
