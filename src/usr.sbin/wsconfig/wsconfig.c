/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

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

__RCSID("$MirOS: src/usr.sbin/wsconfig/wsconfig.c,v 1.7 2006/11/16 21:34:37 tg Exp $");

#define DEFDEV	"/dev/ttyCcfg"

/* query string sent to the terminal for LC_CTYPE detection */
/* XXX is U+00A0 ok or some other char better? Think EUC, SJIS, etc. */
const char ctype_qstr[] = "\030\032\r\xC2\xA0\033[6n";

__dead void usage(void);

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
main(int argc, char **argv)
{
	const char *wsdev, *est;
	char buf[64];
	int wsfd, c, rv = 0;
	int action, nr = 0, q = 0;
	struct termios tio, otio;
	struct wsdisplay_font f;

	wsdev = DEFDEV;
	action = 0;

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
				action = 6;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!action)
		usage();

	if (wsdev == DEFDEV && (action == 4 || action == 6))
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
		break;
	default:
		usage();
	}

	close(wsfd);
	return (rv);
}

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
