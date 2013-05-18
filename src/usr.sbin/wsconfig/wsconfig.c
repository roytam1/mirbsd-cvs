/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

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
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFDEV	"/dev/ttyCcfg"

__dead void usage(void);

int
main(int argc, char **argv)
{
	const char *wsdev, *est;
	int wsfd, c, action, nr = 0, rv = 0;

	wsdev = DEFDEV;
	action = 0;

	while ((c = getopt(argc, argv, "f:s:")) != -1)
		switch (c) {
		case 'f':
			wsdev = optarg;
			break;
		case 's':
			action = 1;
			nr = strtonum(optarg, 0, 255, &est);
			if (est)
				errx(1, "console number %s is %s", optarg, est);
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!action)
		usage();

	if ((wsfd = open(wsdev, O_RDWR, 0)) < 0)
		err(2, "open %s", wsdev);

	switch (action) {
	case 1:
		if (argc)
			usage();
		if (ioctl(wsfd, VT_ACTIVATE, nr) == -1)
			err(3, "ioctl VT_ACTIVATE %d", nr);
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

	fprintf(stderr, "Usage:\n"
	    "%s [-f ctldev] -s screen\n",
	    __progname);
	exit(1);
}
