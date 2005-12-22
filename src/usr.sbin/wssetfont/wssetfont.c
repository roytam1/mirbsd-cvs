/* $MirOS$ */

/*
 * Copyright (c) 2004
 *	Benjamin Lewis.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <err.h>

#include <dev/wscons/wsconsio.h>

__RCSID("$MirOS$");

#define CFG_DEV		"/dev/ttyCcfg"

int main(int, char**);
static void usage(void);

static void
usage()
{
	extern char *__progname;

	(void)fprintf(stderr,
		      "usage: %s [-c cfgdev] [-t ttydev] [-s slot | name]\n",
		      __progname);
	exit(1);
}

int
main(argc, argv)
	int argc;
	char **argv;
{
	char *cfg_dev, *tty_dev;
	struct wsdisplay_font f;
	int res;
	int c, sflag;
	int cfg_fd, tty_fd;

	cfg_dev = CFG_DEV;
 	tty_dev = ttyname(STDIN_FILENO);
	f.index = -1;
	f.name[0] = '\0';
	sflag = 0;

	while ((c = getopt(argc, argv, "c:t:s:")) != -1) {
		switch (c) {
		case 'c':
			cfg_dev = optarg;
			break;
		case 't':
			tty_dev = optarg;
			break;
		case 's':
		        sflag++;
			if (sscanf(optarg, "%d", &f.index) != 1)
				errx(1, "invalid slot number %d", f.index);
			break;
		case '?':
		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (sflag + argc > 1)
		usage();
	if (!sflag && argc == 0) {
		f.index = 0;
		sflag = 1;
	}
	if (!sflag)
		strlcpy(f.name, argv[0], WSFONT_NAME_SIZE);

	cfg_fd = open(cfg_dev, O_RDONLY, 0);
	if (cfg_fd < 0)
		err(1, "open %s", cfg_dev);
	tty_fd = open(tty_dev, O_WRONLY, 0);
	if (tty_fd < 0)
		err(1, "open %s", tty_dev);

	if (sflag) {
		res = ioctl(cfg_fd, WSDISPLAYIO_LSFONT, &f);
		if (res) err(1, "WSDISPLAYIO_LSFONT");
	}
	res = ioctl(tty_fd, WSDISPLAYIO_USEFONT, &f);
	if (res) err(1, "WSDISPLAYIO_USEFONT");
}
