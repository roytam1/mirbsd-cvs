/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <sys/cdefs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

__RCSID("$MirOS$");

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
