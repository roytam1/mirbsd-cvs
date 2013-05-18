/* $MirOS: src/usr.sbin/wsconfig/wsconfig.c,v 1.11 2007/02/18 01:15:11 tg Exp $ */

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
#include <sys/ioctl.h>
#include <dev/wscons/wsconsio.h>
#include <dev/wscons/wsdisplay_usl_io.h>
#include <dev/wscons/wsdisplayvar.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

__RCSID("$MirOS: src/usr.sbin/wsconfig/wsconfig.c,v 1.11 2007/02/18 01:15:11 tg Exp $");

#define DEFDEV	"/dev/ttyCcfg"

/* query string sent to the terminal for LC_CTYPE detection */
/* XXX is U+20AC U+002E ok or some other char better? Think EUC, SJIS, etc. */
const char ctype_qstr[] = "\030\032\r\xE2\x82\xAC.\033[6n";

#ifndef SMALL
__dead void usage(void);
#endif

/*
 * common options:
 * -f <device>		select device on which to operate
 * -q			be more quiet
 * -?			help
 *
 *
 * operation modes:
 *
 * === default device: /dev/ttyCcfg ===
 * -I <number>		dump info about font in slot #number
 * -S			print out active VT number
 * -s <number>		activate VT #number
 *
 * === default device: ttyname(stdin) ===
 * -o <name>		select font #name
 * -U			return true and print (unless -q) if VT is UTF-8
 */

int
#ifdef SMALL
main(void)		/* like -U -q */
#else
main(int argc, char **argv)
#endif
{
	const char *wsdev, *est;
	char buf[64];
	int wsfd, c, rv = 0;
	int action = 0, nr = 0;
	struct termios tio, otio;
#ifndef SMALL
	struct wsdisplay_font f;
	int q = 0;

	wsdev = DEFDEV;
	while ((c = getopt(argc, argv, "f:I:o:qSs:U")) != -1)
		switch (c) {
		case 'f':
			wsdev = optarg;
			break;
		case 'I':
			if (action)
				usage();
			else
				action = 5;
			nr = strtonum(optarg, 0, WSDISPLAY_MAXFONT - 1, &est);
			if (est)
				errx(1, "slot number %s is %s", optarg, est);
			f.index = nr;
			break;
		case 'o':
			if (action)
				usage();
			else
				action = 4;
			strlcpy(f.name, optarg, WSFONT_NAME_SIZE);
			break;
		case 'q':
			q = 1;
			break;
		case 'S':
			if (action)
				usage();
			else
				action = 2;
			break;
		case 's':
			if (action)
				usage();
			else
				action = 1;
			nr = strtonum(optarg, 1, 255, &est);
			if (est)
				errx(1, "console number %s is %s", optarg, est);
			break;
		case 'U':
			if (action)
				usage();
			else
#endif
				action = 6;
#ifndef SMALL
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!action)
		usage();

	if (wsdev == DEFDEV && (action == 4 || action == 6))
#endif
		if ((wsdev = ttyname(STDIN_FILENO)) == NULL)
			wsdev = "/dev/tty";

	/* apparently O_RDONLY wouldn't matter but we stay safe */
	if ((est = ttyname(STDIN_FILENO)) != NULL && !strcmp(wsdev, est))
		wsfd = STDIN_FILENO;
	else if ((est = ttyname(STDOUT_FILENO)) != NULL && !strcmp(wsdev, est))
		wsfd = STDOUT_FILENO;
	else
		if ((wsfd = open(wsdev, O_RDWR, 0)) < 0)
			err(2, "open %s", wsdev);

#ifndef SMALL
	switch (action) {
	case 1:
		if (argc)
			usage();
		if (ioctl(wsfd, VT_ACTIVATE, nr) == -1)
			err(3, "ioctl VT_ACTIVATE %d", nr);
		break;
	case 2:
		if (argc)
			usage();
		if (ioctl(wsfd, VT_GETACTIVE, &nr) == -1)
			err(3, "ioctl VT_GETACTIVE");
		printf("%d\n", nr);
		break;
	case 4:
		if (ioctl(wsfd, WSDISPLAYIO_USEFONT, &f) == -1)
			err(3, "ioctl WSDISPLAYIO_USEFONT");
		if (!q)
			printf("selected font \"%s\"\n", f.name);
		break;
	case 5:
		if (ioctl(wsfd, WSDISPLAYIO_LSFONT, &f) == -1)
			err(3, "ioctl WSDISPLAYIO_LSFONT");
		if (q)
			printf("%s\n", f.name);
		else {
			printf("%32s%s\n", "Name:", f.name);
			printf("%32s%d\n", "Index:", f.index);
			printf("%32s%d\n", "First Character:", f.firstchar);
			printf("%32s%d\n", "Number of Characters:", f.numchars);
			printf("%32s%d\n", "Last Character:",
			    f.firstchar + f.numchars);
			if ((unsigned)f.encoding < 5)
				printf("%32s%s\n", "Encoding:",
				    (f.encoding == 0) ? "ISO (latin1)" :
				    (f.encoding == 1) ? "IBM (437)" :
				    (f.encoding == 2) ? "PCVT (special)" :
				    (f.encoding == 3) ? "ISO7 (greek)" :
				    "SONY");
			else
				printf("%32sUNKNOWN (%d)\n",
				    "Encoding:", f.encoding);
			printf("%32s%u\n", "Font Width:", f.fontwidth);
			printf("%32s%u\n", "Font Height:", f.fontheight);
			printf("%32s%u\n", "Font Stride:", f.stride);
			if ((unsigned)f.bitorder < 3)
				printf("%32s%s\n", "Bit Order:",
				    (f.bitorder == 0) ? "KNOWN (host)" :
				    (f.bitorder == 1) ? "L2R" : "R2L");
			else
				printf("%32sUNKNOWN (%d)\n",
				    "Bit Order:", f.bitorder);
			if ((unsigned)f.byteorder < 3)
				printf("%32s%s\n", "Byte Order:",
				    (f.byteorder == 0) ? "KNOWN (host)" :
				    (f.byteorder == 1) ? "L2R" : "R2L");
			else
				printf("%32sUNKNOWN (%d)\n",
				    "Byte Order:", f.byteorder);
		}
		break;
	case 6:
#endif
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
		if ((size_t)write(wsfd, ctype_qstr, strlen(ctype_qstr)) !=
		    strlen(ctype_qstr)) {
			warn("write\r");
			goto tios_err;
		}
		/* delay for 50 ms */
		{
			struct timeval t;

			t.tv_sec = 0;
			t.tv_usec = 50 * 1000;
			select(0, NULL, NULL, NULL, &t);
		}
		nr = read(wsfd, buf, sizeof (buf));
		rv = /* unknown */ 1;
		if (nr > 5 && buf[0] == 033 && buf[1] == '[') {
			c = 2;
			while (c < (nr - 2))
				if (buf[c++] == ';')
					break;
		if (buf[c - 1] == ';' &&
		    (buf[c] == '3' || buf[c] == '4') &&
		    !isdigit(buf[c + 1]))
			rv = buf[c] == '4' ? /* latin1 */ 2 : /* utf-8 */ 0;
		}
		write(wsfd, "\r      \r", 8);
 tios_err:
		if (tcflush(wsfd, TCIOFLUSH))
			warn("tcflush");
		if (tcsetattr(wsfd, TCSANOW, &otio))
			err(3, "tcsetattr");
#ifndef SMALL
		if (!q)
			printf("LC_CTYPE=%s; export LC_CTYPE\n",
			    rv == 0 ? "en_US.UTF-8" : "C");
		if (!q && rv > 2)
			puts("# warning: problems occured!\n");
		break;
	default:
		usage();
	}
#endif

	close(wsfd);
	return (rv);
}

#ifndef SMALL
void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "Usage:\t%s -U\n"
	    "\t%s [-f ctldev] -s screen\n"
	    "\t%s [-q] [-f wsdev] { -I slot | -o name }\n",
	    __progname, __progname, __progname);
	exit(1);
}
#endif
