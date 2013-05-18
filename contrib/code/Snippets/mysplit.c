/* $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
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
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <regex.h>
#include <err.h>

#ifdef	DEBUG
#define	D(x, ...)	fprintf(stderr, "deb: " x "\n", __VA_ARGS__);
#else
#define	D(x, ...)
#endif

#define	FNAM	"split.%016llX"	/* file name template */
#define	FNAMLEN	128	/* max. file name length */
#define	BUFLEN	2048	/* check in N byte chunks (fragsiz) */
#define	CHKLEN	80	/* check first N bytes */
 /* regex to check for */
#define	CHKEXP	"[A-Za-z0-9_ \n\t-]{5,}[\t\n -~]{6,}[A-Za-z0-9_ \n\t-]{5,}"

char fnbuf[FNAMLEN], fdbuf[BUFLEN];

int
main(int argc, char *argv[])
{
	int64_t num = 0;
	int ifd, fd = 0, rt;
	size_t b;
	regex_t re;
	regmatch_t pmatch;

	if (argc > 1) {
		if ((ifd = open(argv[1], O_RDONLY, 0)) == -1)
			err(1, "open input");
	} else
		ifd = 0;
	D("ifd = %d", ifd);

	if ((rt = regcomp(&re, CHKEXP, REG_EXTENDED | REG_NOSUB))) {
		regerror(rt, &re, fdbuf, BUFLEN);
		regfree(&re);
		fprintf(stderr, "error %d in RE: %s\n", rt, fdbuf);
		return 1;
	}
	pmatch.rm_so = 0;
	pmatch.rm_eo = CHKLEN;

	while ((b = read(ifd, fdbuf, BUFLEN))) {
		rt = regexec(&re, fdbuf, 0, &pmatch,
		    REG_NOTBOL | REG_NOTEOL | REG_STARTEND);
		D("b = %d; rt = %d (%s)", b, rt, (rt == REG_NOMATCH) ?
		    "no match" : ((rt == 0) ? "match" : "error"));
		if (rt == REG_NOMATCH)
			continue;
		if (rt) {
			regerror(rt, &re, fdbuf, BUFLEN);
			regfree(&re);
			fprintf(stderr, "error in RE on %s: %s\n",
			    fnbuf, fdbuf);
			return 1;
		}
		if (!fd) {
			snprintf(fnbuf, FNAMLEN, FNAM, num++);
			if ((fd = open(fnbuf, O_WRONLY | O_CREAT | O_EXCL,
			    0400)) == -1)
				err(1, "open");
			D("opened %s to fd %d", fnbuf, fd);
		}
		while ((b) && (!fdbuf[b - 1]))
			--b;
		if ((size_t)write(fd, fdbuf, b) != b) {
			fprintf(stderr, "warning: could not write"
			    " %d bytes to file %s", b, fnbuf);
		}
		if ((b != BUFLEN) ||
		    !(fdbuf[BUFLEN - 1]) || !(fdbuf[BUFLEN - 2])) {
			D("closing, b=%d, fdbuf=%02X%02X", b,
			    fdbuf[BUFLEN - 2], fdbuf[BUFLEN - 1]);
			if (close(fd))
				fprintf(stderr, "warning: close on %s", fnbuf);
			fd = 0;
		} else {
			D("looping over, b=%d, fdbuf=%02X%02X", b,
			    fdbuf[BUFLEN - 2], fdbuf[BUFLEN - 1]);
		}
	}
	if (fd)
		close(fd);
	regfree(&re);
	return 0;
}
