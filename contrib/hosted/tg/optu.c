#if 0
.if "0" == "1"
#endif

/*-
 * Copyright © 2012
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
 */

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <wchar.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

static char d[MB_CUR_MAX];

int
main(int argc, char *argv[])
{
	char *cp, *buf = NULL;
	size_t bufsz = 0, buflen = 0, s;
	ssize_t ss;
	enum { INV, ENC, VIS, DEC } mode = INV;
	int c;
	wchar_t wc;

	while ((c = getopt(argc, argv, "dev")) != -1)
		switch (c) {
		case 'd':
			mode = DEC;
			break;
		case 'e':
			mode = ENC;
			break;
		case 'v':
			mode = VIS;
			break;
		default:
 usage:
			fprintf(stderr, "Usage: optu -d | -e | -v\n");
			return (1);
		}
	if (mode == INV || (argc -= optind))
		goto usage;

 rdloop:
	if (bufsz - buflen == 0) {
		if (bufsz) {
			if (bufsz > (SIZE_MAX - bufsz - 2))
				errx(1, "out of memory after %zu bytes", bufsz);
			bufsz += bufsz;
		} else {
			bufsz = 4096;
		}
		if (!(buf = realloc(buf, bufsz)))
			err(1, "could not allocate %zu bytes", bufsz);
	}
	if ((ss = read(STDIN_FILENO, buf + buflen, bufsz - buflen)) == -1) {
		if (errno == EINTR)
			goto rdloop;
		err(1, "read");
	} else if (ss != 0) {
		if ((size_t)ss > (bufsz - buflen))
			errx(1, "got %zu bytes, wanted to read %zu only",
			    (size_t)ss, bufsz - buflen);
		buflen += (size_t)ss;
		goto rdloop;
	}

	/* EOF on input */

	if (buflen == 0)
		return (0);

	if (mode == ENC && (buflen & 1) != 0)
		errx(1, "encoding odd number of bytes %zu impossible", buflen);

	bufsz = buflen;
	if (!(buf = realloc(buf, bufsz)))
		err(1, "could not resize to %zu bytes", bufsz);

	if (mode == ENC) {
		wchar_t *wp = (void *)buf;
 wrloop_enc:
		if ((s = optu16to8(d, *wp++, NULL)) == (size_t)-1)
			err(1, "optu16to8");
		if ((size_t)write(STDOUT_FILENO, d, s) != s)
			err(1, "writing %zu octets", s);
		if ((size_t)(((char *)wp) - buf) < buflen)
			goto wrloop_enc;
		return (0);
	}

	/* decode (visually or not) */
	cp = buf;
 wrloop_dec:
	s = buflen - (cp - buf);
 wrloop_finish:
	if ((ss = (ssize_t)(mode == VIS ? optu8to16vis : optu8to16)(&wc, cp,
	    s, NULL)) == (ssize_t)-2) {
		if (s == 0)
			return (0);
		cp += s;
		goto wrloop_dec;
	} else if (ss == (ssize_t)-1)
		err(255, "%s returned (size_t)-1", mode == VIS ?
		    "optu8to16vis" : "optu8to16");
	if ((size_t)write(STDOUT_FILENO, &wc, sizeof(wc)) != sizeof(wc))
		err(1, "writing %zu octets (one wide character)", sizeof(wc));
	if (s == 0)
		goto wrloop_finish;
	cp += ss;
	if ((size_t)(cp - buf) < buflen)
		goto wrloop_dec;
	return (0);
}

#if 0
.endif

PROG=		optu
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
