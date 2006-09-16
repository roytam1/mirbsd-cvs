/* $MirOS: contrib/hosted/fwcf/mkfwcf/mkfwcf.c,v 1.7 2006/09/16 04:40:25 tg Exp $ */

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
#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "compress.h"
#include "fts_subs.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/mkfwcf/mkfwcf.c,v 1.7 2006/09/16 04:40:25 tg Exp $");

static int unfwcf(int, const char *);
static int list_compressors(void);
static __dead void usage(void);

int
main(int argc, char *argv[])
{
	int c;
	int fd = STDIN_FILENO;
	const char *file_root = NULL, *infile = NULL;

	while ((c = getopt(argc, argv, "i:l")) != -1)
		switch (c) {
		case 'i':
			infile = optarg;
			break;
		case 'l':
			return (list_compressors());
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	file_root = *argv;

	if (infile != NULL)
		if ((fd = open(infile, O_RDONLY, 0)) < 0)
			err(1, "open %s", infile);

	return (unfwcf(fd, file_root));
}

static __dead void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:\t%s [-i <infile>] <directory>"
	    "\n\t%s -l\n", __progname, __progname);
	exit(1);
}

static int
unfwcf(int fd, const char *dir __attribute__((unused)))
{
	uint8_t c, hdrbuf[12];
	size_t outer, inner;
	fwcf_compressor *complist;
	char *cdata, *udata;
	uint32_t x;

	if (read(fd, hdrbuf, 12) != 12)
		err(1, "read");

	if (strncmp((const char *)hdrbuf, "FWCF", 4))
		errx(1, "file format error");

	outer = hdrbuf[4] | (hdrbuf[5] << 8) | (hdrbuf[6] << 16);
	if (hdrbuf[7] != FWCF_VER)
		errx(1, "wrong file version %02Xh", hdrbuf[7]);
	inner = hdrbuf[8] | (hdrbuf[9] << 8) | (hdrbuf[10] << 16);
	c = hdrbuf[11];

	if ((complist = compress_enumerate()) == NULL)
		errx(1, "compress_enumerate");
	if (complist[c].name == NULL)
		errx(1, "compression algorithm %02Xh not found", c);
	if (complist[c].init())
		errx(1, "cannot initialise %s compression",
		     complist[c].name);

	if (((cdata = malloc(outer)) == NULL) ||
	    ((udata = malloc(inner)) == NULL))
		err(1, "malloc");
	memcpy(cdata, hdrbuf, 12);
	if ((size_t)read(fd, cdata + 12, outer - 12) != (outer - 12))
		err(1, "read");
	memcpy(hdrbuf, cdata + outer - 4, 4);
	{
		uint8_t *buf = (uint8_t *)cdata;
		unsigned s1 = 1, s2 = 0, n, len = outer - 4;

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
		while (len) {
			len -= (n = MIN(len, NMAX));
			while (n--) {
				s1 += *buf++;
				s2 += s1;
			}
			s1 %= BASE;
			s2 %= BASE;
		}
#undef BASE
#undef NMAX
		if (((hdrbuf[0] | ((unsigned)hdrbuf[1] << 8)) != s1) ||
		    ((hdrbuf[2] | ((unsigned)hdrbuf[3] << 8)) != s2))
			errx(1, "crc mismatch: %02X%02X%02X%02X != %04X%04X",
			    hdrbuf[3], hdrbuf[2], hdrbuf[1], hdrbuf[0], s2, s1);
	}

	if ((x = complist[c].decompress(udata, inner, cdata + 12,
	    outer - 12)) != inner)
		errx(1, "size mismatch: decompressed %d, want %d", x, inner);
	free(cdata);

	return ((size_t)write(1, udata, inner) == inner ? 0 : 1);
}

static int
list_compressors(void)
{
	int rv;

	printf("List of registered compressors:\n");
	if ((rv = compress_list()))
		printf("No compressor registered!\n");
	return (rv);
}
