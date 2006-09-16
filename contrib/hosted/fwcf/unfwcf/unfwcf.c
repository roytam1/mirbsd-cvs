/* $MirOS: contrib/hosted/fwcf/unfwcf/unfwcf.c,v 1.1 2006/09/16 05:52:09 tg Exp $ */

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
#include "adler.h"
#include "compress.h"
#include "fts_subs.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/unfwcf/unfwcf.c,v 1.1 2006/09/16 05:52:09 tg Exp $");

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
	size_t outer, inner, x;
	char *cdata, *udata;

	if (read(fd, hdrbuf, 12) != 12)
		err(1, "read");

	if (strncmp((const char *)hdrbuf, "FWCF", 4))
		errx(1, "file format error");

	outer = LOADT(hdrbuf + 4);
	if (hdrbuf[7] != FWCF_VER)
		errx(1, "wrong file version %02Xh", hdrbuf[7]);
	inner = LOADT(hdrbuf + 8);
	c = hdrbuf[11];

	if (((cdata = malloc(outer)) == NULL) ||
	    ((udata = malloc(inner)) == NULL))
		err(1, "malloc");
	memcpy(cdata, hdrbuf, 12);
	if ((size_t)read(fd, cdata + 12, outer - 12) != (outer - 12))
		err(1, "read");

	ADLER_START(cdata)
	unsigned len = outer - 4;
	ADLER_RUN
	if ((s1 != LOADW(cdata + outer - 4)) ||
	    (s2 != LOADW(cdata + outer - 2)))
		errx(1, "crc mismatch: %02X%02X%02X%02X != %04X%04X",
		    cdata[outer - 1], cdata[outer - 2], cdata[outer - 3],
		    cdata[outer - 4], s2, s1);
	ADLER_END

	if ((x = compressor_get(c)->decompress(udata, inner, cdata + 12,
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
