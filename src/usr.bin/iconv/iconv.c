/* $MirOS: src/usr.bin/iconv/iconv.c,v 1.2 2007/07/05 23:09:41 tg Exp $ */

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
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 *-
 * SUSv3 conformant iconv(1) for libcitrus_iconv in MirOS
 */

#define _ALL_SOURCE
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <iconv.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/usr.bin/iconv/iconv.c,v 1.2 2007/07/05 23:09:41 tg Exp $");

__dead void dump_csets(void);
__dead void usage(void);

extern const char *__progname;

#define CBUFSZ	65536

char ibuf[CBUFSZ], obuf[CBUFSZ * 16];
char static_fn[] = "<stdin>";

int
main(int argc, char *argv[])
{
	bool flag_c = false, flag_s = false;
	const char *fromcs = NULL, *tocs = NULL;
	char *fn, *srcp, *dstp;
	int c, fd = STDIN_FILENO;
	size_t m, n, ilen, olen, inval = 0, invaltot = 0;
	iconv_t cd;
	off_t iofs;

	setlocale(LC_ALL, "");

	while ((c = getopt(argc, argv, "cf:lst:")) != -1)
		switch (c) {
		case 'c':
			flag_c = true;
			break;
		case 'f':
			fromcs = optarg;
			break;
		case 'l':
			dump_csets();
			break;
		case 's':
			flag_s = true;
			break;
		case 't':
			tocs = optarg;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (fromcs == NULL)
#ifdef __MirBSD__
		fromcs = "UTF-8";
#else
		fromcs = nl_langinfo(CODESET);
#endif

	if (tocs == NULL)
#ifdef __MirBSD__
		tocs = "UTF-8";
#else
		tocs = nl_langinfo(CODESET);
#endif

#ifdef DEBUG
	fprintf(stderr, "D: initialising conversion %s -> %s\n", fromcs, tocs);
#endif
	if ((cd = iconv_open(tocs, fromcs)) == (iconv_t)-1) {
		if (errno == EINVAL)
			err(2, "cannot convert from %s to %s", fromcs, tocs);
		else
			err(1, "iconv_open");
	}

	do {
		fn = argc ? *argv++ : NULL;
		if ((fn == NULL) || !strcmp(fn, "-")) {
			fn = static_fn;		/* for errors */
			fd = STDIN_FILENO;
		} else if ((fd = open(fn, O_RDONLY, 0)) == -1)
			err(1, "open: %s", fn);
		ilen = 0;
		iofs = 0;
#ifdef DEBUG
		fprintf(stderr, "D: new file %s\n", fn);
#endif

 read_loop:
#ifdef DEBUG
		fprintf(stderr, "D: loop with %zd already in\n", ilen);
#endif
		if (n = 0, (ilen < sizeof (ibuf)) && ((n = (size_t)read(fd,
		    ibuf + ilen, sizeof (ibuf) - ilen)) == (size_t)-1))
			err(1, "read %zd bytes from %s",
			    sizeof (ibuf) - ilen, fn);
#ifdef DEBUG
		fprintf(stderr, "D: read %zd bytes\n", n);
#endif

		ilen += n;
		if (ilen == 0)
			goto next_file;
		olen = sizeof (obuf);
		srcp = ibuf;
		dstp = obuf;
#ifdef DEBUG
		fprintf(stderr, "D: doing iconv on %zd bytes\n", ilen);
#endif
		if (__iconv(cd, (const char **)&srcp, &ilen, &dstp, &olen,
		    0, &m) == (size_t)-1) {
			c = errno;
#ifdef DEBUG
			fprintf(stderr, "D: failed for %s\n", strerror(c));
#endif
			if (c == E2BIG)
				err(3, "Output buffer too small, please"
				    " report to the maintainer");
			else if (c == EINVAL) {
				if (srcp == ibuf) {
					if (!flag_s)
						fprintf(stderr,
						    "%s: %s terminates with an"
						    " incomplete character or"
						    " shift sequence!\n",
						    __progname, fn);
					goto next_file;
				}
			} else if (c == EILSEQ) {
				if (!flag_s)
					fprintf(stderr, "%s: invalid source"
					    " character 0x%02X in %s at"
					    " offset %llu\n",
					    __progname, (u_char)*srcp, fn,
					    (uint64_t)iofs + (srcp - ibuf));
				if (!flag_c)
					errx(1, "run with -c to ignore");
				++srcp;
				--ilen;
			} else
				err(1, "iconv (%s -> %s) in file %s",
				    fromcs, tocs, fn);
		}
#ifdef DEBUG
		fprintf(stderr, "D: converted %td bytes, rest %zd\n",
		     srcp - ibuf, ilen);
#endif
		iofs += srcp - ibuf;
		if (ilen)
			memmove(ibuf, srcp, ilen);
		inval += m;
		write(STDOUT_FILENO, obuf, dstp - obuf);
#ifdef DEBUG
		fprintf(stderr, "D: wrote %td bytes, %zd invals\n",
		    dstp - obuf, m);
#endif
		goto read_loop;

 next_file:
		close(fd);
#ifdef DEBUG
		fprintf(stderr, "D: end of file %s (%llu bytes)\n", fn,
		    (uint64_t)iofs);
#endif
		if (inval && !flag_s)
			fprintf(stderr, "%s: information loss of %zd"
			    " characters from %s\n",
			    __progname, inval, fn);
		invaltot += inval;
		dstp = obuf;
		olen = sizeof (obuf);
		/* place into initial conversion state */
		if (iconv(cd, NULL, NULL, &dstp, &olen) != (size_t)-1)
			write(STDOUT_FILENO, obuf, dstp - obuf);

		if (argc == 0)
			break;
	} while (--argc);

	iconv_close(cd);
	if (invaltot && !flag_s)
		fprintf(stderr, "%s: information loss of %zd characters"
		    " in total\n", __progname, invaltot);
	return (0);
}

__dead void
usage(void)
{
	fprintf(stderr, "Syntax:\t%s -l\n"
	    "\t%s [-cs] [-f fromcs] [-t tocs] [file ...]\n",
	    __progname, __progname);
	exit(1);
}

__dead void
dump_csets(void)
{
	char **names;
	size_t num;

	if (__iconv_get_list(&names, &num))
		err(1, "__iconv_get_list");

	while (num--)
		printf("%s\n", *names++);
	exit(0);
}
