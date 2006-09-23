/* $MirOS: contrib/hosted/fwcf/fwcf.helper.c,v 1.2 2006/09/23 23:21:04 tg Exp $ */

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

#include "defs.h"
#include "compress.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/fwcf.helper.c,v 1.2 2006/09/23 23:21:04 tg Exp $");

static __dead void usage(void);
static int mkfwcf(int, const char *, int);
static int unfwcf(int, const char *);

int
main(int argc, char *argv[])
{
	int c;
	int mode = 0, doempty = 0;
	const char *file_root = NULL;
	fwcf_compressor *cl;

	while ((c = getopt(argc, argv, "elMU")) != -1)
		switch (c) {
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

	if (!mode || ((mode == 2) && doempty))
		usage();

	if (argc != (1 - doempty))
		usage();

	file_root = *argv;

	if (mode == 2)
		return (unfwcf(STDIN_FILENO, file_root));

	if ((cl = compress_enumerate()) != NULL)
		for (c = 0; c < 256; ++c)
			if (cl[c].name != NULL)
				break;

	if ((cl == NULL) || (c == 256))
		errx(1, "no compression algorithms found");

	return (mkfwcf(STDOUT_FILENO, doempty ? NULL : file_root, c));
}

static __dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:\t%s -M {-e | <directory>}"
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
