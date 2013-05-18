/* $MirOS: src/usr.bin/crunch/crunch.c,v 1.1.7.1 2005/03/06 16:46:48 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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

#include <sys/cdefs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

__RCSID("$MirOS: src/usr.bin/crunch/crunch.c,v 1.1.7.1 2005/03/06 16:46:48 tg Exp $");

extern int crunchgen_main(int, char **);
extern int crunchide_main(int, char **);
__dead void usage(void);

int
main(int argc, char **argv)
{
	char *p;

	if (argv == NULL || *argv == NULL || **argv == '\0')
		usage();

	p = strrchr(*argv, '/');
	p = (p == NULL) ? *argv : p + 1;

	if (!strcmp(p, "crunchgen"))
		return crunchgen_main(argc, argv);
	if (!strcmp(p, "crunchide"))
		return crunchide_main(argc, argv);
	usage();
}

__dead void
usage(void)
{
	fprintf(stderr, "Usage:\n\tcrunchgen %s\n\t    %s\n\tcrunchide %s\n",
	    "[-Efq] [-c c-file-name] [-D src-root] [-e exec-file-name]",
	    "[-L lib-dir] [-m makefile-name] conf-file",
	    "[-f keep-list-file] [-k keep-symbol] object-file ...");
	exit(1);
}
