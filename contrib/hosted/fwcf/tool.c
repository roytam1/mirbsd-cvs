/* $MirOS: contrib/hosted/fwcf/tool.c,v 1.3 2007/02/28 22:59:38 tg Exp $ */

/*-
 * Copyright (c) 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
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
#include <unistd.h>

#include "defs.h"
#include "adler.h"
#include "compress.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/tool.c,v 1.3 2007/02/28 22:59:38 tg Exp $");

static __dead void usage(void);
static int mkfwcf(int, const char *, int);
static int unfwcf(int, const char *);
#ifndef SMALL
static int refwcf(int, int, int);
#endif
static int fsopen(const char *, int, int);

int
main(int argc, char *argv[])
{
	int c;
	int mode = 0, doempty = 0;
	int ifd, ofd;
#ifdef SMALL
	int calg = -1;
#else
	int calg = 0;
	const char *infile = NULL, *outfile = NULL;
#endif
	const char *dfile = NULL;
	const char *file_root = NULL;
	fwcf_compressor *cl;

#ifdef SMALL
	while ((c = getopt(argc, argv, "D:elMU")) != -1)
#else
	while ((c = getopt(argc, argv, "C:cD:dei:lMo:RU")) != -1)
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
#endif
		case 'D':
			if (doempty)
				usage();
			dfile = optarg;
			break;
#ifndef SMALL
		case 'd':
			mode = 3;
			break;
#endif
		case 'e':
			if (dfile != NULL)
				usage();
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
		if (argc != ((dfile == NULL) ? (1 - doempty) : 0))
			usage();
		break;
	case 2:
		if (argc != ((dfile == NULL) ? 1 : 0))
			usage();
		break;
#ifndef SMALL
	case 3:
	case 4:
		if (argc || doempty || (dfile != NULL))
			usage();
		break;
#endif
	default:
		usage();
	}
	if (argc)
		file_root = *argv;
#ifdef SMALL
	ifd = STDIN_FILENO;
	ofd = STDOUT_FILENO;
#else
	ifd = fsopen(infile, O_RDONLY, STDIN_FILENO);
	ofd = fsopen(outfile, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
#endif

	if (mode == 2 && dfile != NULL) {
		char *data;
		uint8_t lenbuf[4], adlerbuf[4];
		size_t sz, len;
		int dfd;
		ADLER_DECL;

		if ((dfd = fsopen(dfile, O_WRONLY | O_CREAT | O_TRUNC,
		    STDOUT_FILENO)) < 0)
			err(1, "open %s", dfile);
		if ((data = fwcf_unpack(ifd, &sz)) == NULL)
			return (1);
		lenbuf[0] = sz & 0xFF;
		lenbuf[1] = (sz >> 8) & 0xFF;
		lenbuf[2] = (sz >> 16) & 0xFF;
		lenbuf[3] = (sz >> 24) & 0xFF;
		len = 4;	/* for ADLER_CALC on lenbuf */
		ADLER_CALC(lenbuf);
		len = sz;	/* for ADLER_CALC on data */
		ADLER_CALC(data);
		adlerbuf[0] = s1 & 0xFF;
		adlerbuf[1] = (s1 >> 8) & 0xFF;
		adlerbuf[2] = s2 & 0xFF;
		adlerbuf[3] = (s2 >> 8) & 0xFF;
		if (write(dfd, adlerbuf, 4) != 4)
			err(1, "short write on %s", dfile);
		if (write(dfd, lenbuf, 4) != 4)
			err(1, "short write on %s", dfile);
		if ((size_t)write(dfd, data, sz) != sz)
			err(1, "short write on %s", dfile);
		close(dfd);
		return (0);
	}

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

#ifndef SMALL
	if (mode == 4)
		return (refwcf(ifd, ofd, calg));
#endif

	if (dfile != NULL) {
		char *udata, *data;
		uint8_t hdrbuf[8];
		size_t sz, isz, len;
		int dfd;
		ADLER_DECL;

		if ((dfd = fsopen(dfile, O_RDONLY, STDIN_FILENO)) < 0)
			err(1, "open %s", dfile);
		if (read(dfd, hdrbuf, 8) != 8)
			err(1, "short read on %s", dfile);
		isz = hdrbuf[4] | (hdrbuf[5] << 8) |
		    (hdrbuf[6] << 16) | (hdrbuf[7] << 24);
		if ((udata = malloc(isz)) == NULL)
			err(255, "out of memory trying to allocate %zu bytes",
			    isz);
		if ((size_t)read(dfd, udata, isz) != isz)
			err(1, "short read on %s", dfile);
		close(dfd);
		len = 4;
		ADLER_CALC(hdrbuf + 4);
		len = isz;
		ADLER_CALC(udata);
		if ((hdrbuf[0] != (s1 & 0xFF)) ||
		    (hdrbuf[1] != ((s1 >> 8) & 0xFF)) ||
		    (hdrbuf[2] != (s2 & 0xFF)) ||
		    (hdrbuf[3] != ((s2 >> 8) & 0xFF)))
			err(2, "checksum mismatch from %s, sz %zu,"
			    " want %02X%02X%02X%02X got %04X%04X",
			    dfile, isz, hdrbuf[3], hdrbuf[2],
			    hdrbuf[1], hdrbuf[0], s2, s1);
		data = fwcf_pack(udata, isz, calg, &sz);
		return ((size_t)write(ofd, data, sz) == sz ? 0 : 1);
	}

	return (mkfwcf(ofd, doempty ? NULL : file_root, calg));
}

static __dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:"
#ifdef SMALL
	    "	%s -M { -D <file> | -e | <directory> }"
	    "\n	%s -U { -D <file> | <directory> }"
	    "\n	%s -l\n", __progname, __progname, __progname);
#else
	    "	%s -M [-c | -C <compressor>] [-o <file>]"
	    "\n	    { -D <file> | -e | <directory> }"
	    "\n	%s [-i <file>] -U { -D <file> | <directory> }"
	    "\n	%s [-i <file>] -d"
	    "\n	%s -R [-c | -C <compressor>] [-i <infile>] [-o <outfile>]"
	    "\n	%s -l\n",
	    __progname, __progname, __progname, __progname, __progname);
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

#ifndef SMALL
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
#endif

static int
fsopen(const char *fn, int mode, int altfd)
{
	return (((fn == NULL) || (*fn == '\0') ||
	    ((fn[0] == '-') && (fn[1] == '\0'))) ? altfd :
	    open(fn, mode, 0666));
}
