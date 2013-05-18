/* $MirOS: src/usr.bin/splitb/splitb.c,v 1.4 2005/03/17 09:27:37 tg Exp $ */

/*-
 * Copyright (c) 2005
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
 *-
 * Inspired by work done for Telefax 400, Deutsche Telekom AG.
 */

#ifdef linux
#define	_FILE_OFFSET_BITS	64
#ifndef __dead
#define	__dead			__attribute__((noreturn))
#endif
#endif

#include <sys/param.h>
#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int, char **);
__dead void usage(int);

int
main(int argc, char **argv)
{
	int i, ifd, ofd, ch, pfl = 3;
	long l = 1, lw = 0, bufsiz = 1024 * 1024;
	ssize_t k;
	bool quiet = false, dec = false;
	char *ft = strdup("split"), fn[PATH_MAX], *buf;
	int64_t sum = 0;

	while ((ch = getopt(argc, argv, "B:b:dhkqt:w:")) != -1) {
		switch (ch) {
		case 'h':
			usage(1);
			break;
		case 'B':
			if ((bufsiz = strtol(optarg, NULL, 0)) <=0)
				errx(1, "bufsize cannot be negative");
			else if ((bufsiz == 1) && !quiet)
				warnx("bufsize 1 provides low performance");
			else if (bufsiz > 1024 * 1024 * 1024)
				errx(1, "bufsize > 1 GiB makes no sense");
			break;
		case 'b':
			if ((l = strtol(optarg, NULL, 0)) <= 0)
				usage(0);
			break;
		case 'd':
			dec = !dec;
			break;
		case 'k':
			bufsiz = 1024;
			break;
		case 'q':
			quiet = true;
			break;
		case 't':
			ft = strdup(optarg);
			break;
		case 'w':
			if ((pfl = (int)strtol(optarg, NULL, 0)) < 1)
				usage(0);
			break;
		default:
			usage(0);
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if ((size_t)pfl > (PATH_MAX - 2 - strlen(ft)))
		usage(0);

	if (argc) {
		if ((ifd = open(*argv, O_RDONLY)) == -1)
			err(1, "cannot open input file");
	} else
		ifd = STDIN_FILENO;

	if ((buf = malloc((size_t)bufsiz)) == NULL)
		err(1, "cannot allocate memory");

	i = 0;
	ofd = -1;
	while ((k = read(ifd, buf, (size_t)bufsiz)) > 0) {
		sum += k;
		if (ofd == -1) {
			snprintf(fn, sizeof(fn),
			    dec ? "%s.%0*d" : "%s.%0*X",
			    ft, pfl, i);
			if ((ofd = open(fn, O_WRONLY | O_CREAT | O_TRUNC,
			    0666)) == -1)
				err(1, "cannot open output file");
			lw = 0;
			if (!quiet)
				printf("Writing to %s...", fn);
			fflush(stdout);
		}
		if (write(ofd, buf, (size_t)k) != k)
			err(1, "cannot write to output file");
		if (k != bufsiz) {
			close(ofd);
			break;
		}
		if (++lw == l) {
			close(ofd);
			ofd = -1;
			if (!quiet)
				printf("done\n");
			fflush(stdout);
			++i;
		}
	}
	if (ofd != -1) {
		close(ofd);
		if (!quiet)
			printf("done\n");
		++i;
	}
	printf("%lld bytes written to %d output files.\n", sum, i);
	return 0;
}

__dead void
usage(int loud)
{
	extern const char *__progname;

	printf("Usage: %s [-dhkq] [-B bufsiz] [-b blocks] [-t template]\n"
	    "    [-w width] [inputfile]\n%s",
	    __progname, loud ?
	    "A buffer consists of bufsiz Bytes, or 1 KiB (1024 Bytes)\n"
	    "if -k is given, or 1 MiB (1048576 Bytes) if neither -B\n"
	    "nor -k is used on the command line. Default width for\n"
	    "the file postfix is 3; stdin is the default inputfile.\n"
	    : "");
	exit(loud ? 0 : 1);
}
