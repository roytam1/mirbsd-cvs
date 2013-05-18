/**	$MirOS: contrib/code/Snippets/mysplit.c,v 1.1.7.1 2005/02/05 02:36:15 tg Exp $ */

/*-
 * Copyright (c) 2004
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
