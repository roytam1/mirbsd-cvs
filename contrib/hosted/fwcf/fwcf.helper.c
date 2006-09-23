/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "compress.h"
#include "pack.h"

static const char __rcsid[] __attribute__((section (".text"))) =
    "$MirOS$";

static __dead void usage(void);
static int mkfwcf(int, const char *, int);
static int unfwcf(int, const char *);

int
main(int argc, char *argv[])
{
	int c;
	int mode = 0, docompress = 0, doempty = 0;
	const char *file_root = NULL;

	while ((c = getopt(argc, argv, "cC:elMU")) != -1)
		switch (c) {
		case 'C':
			if (!(docompress = strtonum(optarg, 1, 255, NULL)))
				usage();
			break;
		case 'c':
			docompress = 1;
			break;
		case 'e':
			doempty = 1;
			break;
		case 'l':
			return (list_compressors());
		case 'M':
			mode = 1;
			break;
		case 'U':
			mode = 2;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!mode || ((mode == 2) && (doempty || docompress)))
		usage();

	if (argc != (1 - doempty))
		usage();

	file_root = *argv;

	if (mode == 2)
		return (unfwcf(STDIN_FILENO, file_root));
	return (mkfwcf(STDOUT_FILENO, doempty ? NULL : file_root, docompress));
}

static __dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:\t%s -M [-e] [-c | -C <algorithm-number>] <directory>"
	    "\n\t%s -U <directory>"
	    "\n\t%s -l\n", __progname, __progname, __progname);
	exit(1);
}

static int
mkfwcf(int fd, const char *dir, int algo)
{
	size_t sz;
	char *data;

	data = fwcf_pack(dir, algo, &sz);
	return ((size_t)write(fd, data, sz) == sz ? 0 : 1);
}

static int
unfwcf(int fd, const char *dir)
{
	char *udata;

	if ((udata = fwcf_unpack(fd)))
			ft_creatm(udata, dir);
	return (udata != NULL ? 0 : 1);
}
