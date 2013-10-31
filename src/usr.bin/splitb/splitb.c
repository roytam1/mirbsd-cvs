/* $MirOS: src/usr.bin/splitb/splitb.c,v 1.6 2008/11/08 23:04:55 tg Exp $ */

/*-
 * Copyright © 2005, 2013
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * Inspired by work done for Telefax 400, Deutsche Telekom AG.
 */

#ifdef linux
#define	_FILE_OFFSET_BITS	64
#ifndef __dead
#define	__dead			__attribute__((__noreturn__))
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
