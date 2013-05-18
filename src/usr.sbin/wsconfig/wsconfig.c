/* $MirOS: src/usr.sbin/wsconfig/wsconfig.c,v 1.6 2006/10/28 18:56:52 tg Exp $ */

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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
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

__RCSID("$MirOS: src/usr.sbin/wsconfig/wsconfig.c,v 1.6 2006/10/28 18:56:52 tg Exp $");

#define DEFDEV	"/dev/ttyCcfg"

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
		strlcpy(buf, "\030\032\r\xC2\xA0\033[6n", sizeof (buf));
		if ((size_t)write(wsfd, buf, strlen(buf)) != strlen(buf)) {
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
