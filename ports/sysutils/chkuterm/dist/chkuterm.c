/* $MirOS: ports/sysutils/chkuterm/dist/chkuterm.c,v 1.10 2007/04/17 23:41:01 tg Exp $ */

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
__RCSID("$miros: src/usr.sbin/wsconfig/wsconfig.c,v 1.16 2007/05/10 13:02:21 tg Exp $");
__RCSID("$MirOS: ports/sysutils/chkuterm/dist/chkuterm.c,v 1.11 2007/05/10 13:02:22 tg Exp $");
__RCSID("$miros: ports/misc/screen/patches/patch-screen_c,v 1.12 2007/05/10 13:02:23 tg Exp $");
#endif

/* query string sent to the terminal for LC_CTYPE detection */
/* XXX is U+20AC U+002E ok or some other char better? Think EUC, SJIS, etc. */
const char ctype_qstr[] = "\030\032\r\xE2\x82\xAC.\033[6n";

/*
 * -U			return true and print (unless -q) if VT is UTF-8
 */

int
main(int argc, char **argv)
{
	const char *wsdev, *est;
	char ch;
	int wsfd, c, rv = 0;
	int nr = 0, q = 0;
	struct termios tio, otio;
	fd_set fds;
	struct timeval tv;
	FILE *wsf;

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
	wsf = fdopen(wsfd, "rb+");

	if (tcgetattr(wsfd, &otio))
		err(3, "tcgetattr");
	tio = otio;
	cfmakeraw(&tio);
	if (tcflush(wsfd, TCIOFLUSH))
		warn("tcflush");
	rv = /* error */ 3;
	if (tcsetattr(wsfd, TCSANOW, &tio)) {
		warn("tcsetattr\r");
		goto tios_err;
	}
	tv.tv_sec = 0;
	tv.tv_usec = 75;
	select(0, NULL, NULL, NULL, &tv);	/* sleep 75 msec */
	if ((size_t)write(wsfd, ctype_qstr, strlen(ctype_qstr)) !=
	    strlen(ctype_qstr)) {
		warn("write\r");
		goto noin;
	}
	select(0, NULL, NULL, NULL, &tv);	/* sleep 75 msec */
	FD_ZERO(&fds);
	FD_SET(wsfd, &fds);
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	if (select(wsfd + 1, &fds, NULL, NULL, &tv) <= 0)
		goto noin;
	nr = read(wsfd, &ch, 1);
	rv = /* unknown */ 1;
	if (wsf != NULL && nr == 1 && ch == 033) {
		unsigned zeile, spalte;

		if (fscanf(wsf, "[%u;%u", &zeile, &spalte) == 2)
			switch (spalte) {
			case 1:	/* EUC-JP, EUC-KR kterm */
			case 5:	/* Shift-JIS kterm */
				break;
			case 3:	/* UTF-8 xterm, screen */
				rv = 0;
				break;
			case 4:	/* ISO-8859-1 xterm, screen */
				rv = 2;
				break;
			default:
				rv = 0x1000 | spalte;
				break;
			}
	}
 noin:
	write(wsfd, "\r      \r", 8);
 tios_err:
	if (tcflush(wsfd, TCIOFLUSH))
		warn("tcflush");
	if (tcsetattr(wsfd, TCSANOW, &otio))
		err(3, "tcsetattr");
	if (rv & 0x1000) {
		/* unknown charset */
		if (!q)
			printf("# unknown column %d\n", rv & 0xFFF);
		rv = 1;
	}
	if (!q)
		printf("LC_CTYPE=%s; export LC_CTYPE\n",
		    rv == 0 ? "en_US.UTF-8" : "C");
	if (!q && rv > 2)
		puts("# warning: problems occured!\n");

	if (wsf == NULL)
		close(wsfd);
	else
		fclose(wsf);
	return (rv);
}
