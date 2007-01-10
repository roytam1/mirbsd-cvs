/* $MirOS: ports/sysutils/chkuterm/dist/chkuterm.c,v 1.3 2007/01/10 00:02:36 tg Exp $ */

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
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#ifdef __RCSID
__RCSID("$miros: src/usr.sbin/wsconfig/wsconfig.c,v 1.8 2007/01/10 00:01:06 tg Exp $");
__RCSID("$MirOS: ports/sysutils/chkuterm/dist/chkuterm.c,v 1.3 2007/01/10 00:02:36 tg Exp $");
#endif

/* query string sent to the terminal for LC_CTYPE detection */
/* XXX is U+00A0 ok or some other char better? Think EUC, SJIS, etc. */
const char ctype_qstr[] = "\030\032\r\xC2\xA0\033[6n";

/*
 * -U			return true and print (unless -q) if VT is UTF-8
 */

int
main(int argc, char **argv)
{
	const char *wsdev, *est;
	char buf[64];
	int wsfd, c, rv = 0;
	int nr = 0, q = 0;
	struct termios tio, otio;

	while ((c = getopt(argc, argv, "qU")) != -1)
		switch (c) {
		case 'q':
			q = 1;
			break;
		}
	argc -= optind;
	argv += optind;

	wsdev = "/dev/tty";

	/* apparently O_RDONLY wouldn't matter but we stay safe */
	if ((est = ttyname(STDIN_FILENO)) != NULL && !strcmp(wsdev, est))
		wsfd = STDIN_FILENO;
	else if ((est = ttyname(STDOUT_FILENO)) != NULL && !strcmp(wsdev, est))
		wsfd = STDOUT_FILENO;
	else
		if ((wsfd = open(wsdev, O_RDWR, 0)) < 0)
			err(2, "open %s", wsdev);

	if (tcgetattr(wsfd, &otio))
		err(3, "tcgetattr");
	tio = otio;
	cfmakeraw(&tio);
	if (tcflush(wsfd, TCIOFLUSH))
		warn("tcflush");
	rv = 3;
	if (tcsetattr(wsfd, TCSANOW, &tio)) {
		warn("tcsetattr\r");
		goto tios_err;
	}
	if ((size_t)write(wsfd, ctype_qstr, strlen(ctype_qstr)) !=
	    strlen(ctype_qstr)) {
		warn("write\r");
		goto tios_err;
	}
	nr = read(wsfd, buf, sizeof (buf));
	rv = 1;
	if (nr > 5 && buf[0] == 033 && buf[1] == '[') {
		c = 2;
		while (c < (nr - 2))
			if (buf[c++] == ';')
				break;
		if (buf[c - 1] == ';' && buf[c] == '2' &&
		    !isdigit(buf[c + 1]))
			rv = 0;
	}
	write(wsfd, "\r   \r", 5);
 tios_err:
	if (tcsetattr(wsfd, TCSAFLUSH, &otio))
		err(3, "tcsetattr");
	if (!q)
		printf("LC_CTYPE=%s; export LC_CTYPE\n",
		    rv == 0 ? "en_US.UTF-8" : "C");
	if (!q && rv > 1)
		puts("# warning: problems occured!\n");

	close(wsfd);
	return (rv);
}
