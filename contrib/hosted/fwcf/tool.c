/* $MirOS: contrib/hosted/fwcf/tool.c,v 1.1 2006/09/24 20:34:59 tg Exp $ */

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

__RCSID("$MirOS: contrib/hosted/fwcf/tool.c,v 1.1 2006/09/24 20:34:59 tg Exp $");

static __dead void usage(void);
static int mkfwcf(int, const char *, int);
static int unfwcf(int, const char *);
static int refwcf(int, int, int);

int
main(int argc, char *argv[])
{
	int c;
	int mode = 0, doempty = 0;
	int ifd = STDIN_FILENO, ofd = STDOUT_FILENO;
#ifdef SMALL
	int calg = -1;
#else
	int calg = 0;
	const char *infile = NULL, *outfile = NULL;
#endif
	const char *file_root = NULL;
	fwcf_compressor *cl;

#ifdef SMALL
	while ((c = getopt(argc, argv, "elMU")) != -1)
#else
	while ((c = getopt(argc, argv, "C:cdei:lMo:RU")) != -1)
#endif
		switch (c) {
#ifndef SMALL
		case 'C':
			if (!(calg = strtonum(optarg, 1, 255, NULL)))
				usage();
			break;
		case 'c':
			calg = -1;
			break;
		case 'd':
			mode = 3;
			break;
#endif
		case 'e':
			doempty = 1;
			break;
#ifndef SMALL
		case 'i':
			infile = optarg;
			break;
#endif
		case 'l':
			return (list_compressors());
		case 'M':
			mode = 1;
			break;
#ifndef SMALL
		case 'o':
			outfile = optarg;
			break;
		case 'R':
			mode = 4;
			break;
#endif
		case 'U':
			mode = 2;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	switch (mode) {
	case 1:
		if (argc != (1 - doempty))
			usage();
		break;
	case 2:
		if (argc != 1)
			usage();
		break;
#ifndef SMALL
	case 3:
	case 4:
		if (argc || doempty)
			usage();
		break;
#endif
	default:
		usage();
	}
	if (argc)
		file_root = *argv;
#ifndef SMALL
	if (infile != NULL)
		if ((ifd = open(infile, O_RDONLY, 0)) < 0)
			err(1, "open %s", infile);
	if (outfile != NULL)
		if ((ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC,
		    0666)) < 0)
			err(1, "open %s", outfile);
#endif

	if ((mode == 2) || (mode == 3))
		return (unfwcf(ifd, (mode == 3) ? NULL : file_root));

	if (calg == -1) {
		if ((cl = compress_enumerate()) != NULL)
			for (calg = 1; calg < 257; ++calg)
				if (cl[calg & 0xFF].name != NULL)
					break;

		if ((cl == NULL) || (calg == 257))
			errx(1, "no compression algorithms found");
		calg &= 0xFF;
	}

	if (mode == 4)
		return (refwcf(ifd, ofd, calg));

	return (mkfwcf(ofd, doempty ? NULL : file_root, calg));
}

static __dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:"
#ifdef SMALL
	    "	%s -M { -e | <directory> }"
	    "\n	%s -U <directory>"
	    "\n	%s -l\n", __progname, __progname, __progname);
	/*
	 * Possible later extension (yes, on the target too):
	 *  "\n	%s -M { -D <file> | -e | <directory> }"
	 *  "\n	%s -U { -D <file> | <directory> }"
	 * where -D saves/restores the intermediate form of
	 * the build-system tool's -R option (i.e. the un-
	 * compressed format of the "inner" filesystem).
	 */
#else
	    "	%s -M [-c | -C <compressor>] [-o <file>] { -e | <directory> }"
	    "\n	%s [-i <file>] {-U <directory> | -d}"
	    "\n	%s -R [-c | -C <compressor>] [-i <infile>] [-o <outfile>]"
	    "\n	%s -l\n", __progname, __progname, __progname, __progname);
#endif
	exit(1);
}

static int
mkfwcf(int fd, const char *dir, int algo)
{
	size_t sz;
	char *data;

	data = fwcf_packm(dir, algo, &sz);
	return ((size_t)write(fd, data, sz) == sz ? 0 : 1);
}

static int
unfwcf(int fd, const char *dir)
{
	char *udata;

	if ((udata = fwcf_unpack(fd, NULL))) {
#ifndef SMALL
		if (dir == NULL)
			ft_dump(udata);
		else
#endif
			ft_creatm(udata, dir);
	}
	return (udata != NULL ? 0 : 1);
}

static int
refwcf(int ifd, int ofd, int algo)
{
	char *udata, *data;
	size_t sz, isz;

	if ((udata = fwcf_unpack(ifd, &isz)) == NULL)
		return (1);
	data = fwcf_pack(udata, isz, algo, &sz);
	return ((size_t)write(ofd, data, sz) == sz ? 0 : 1);
}
