/* $OpenBSD: crunched_main.c,v 1.5 2003/01/27 19:41:30 deraadt Exp $	 */

/*
 * Copyright (c) 2007 Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 1994 University of Maryland
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of U.M. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  U.M. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * U.M. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL U.M.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: James da Silva, Systems Design and Analysis Group
 *			   Computer Science Department
 *			   University of Maryland at College Park
 */

/*
 * crunched_main.c - main program for crunched binaries, it branches to a
 * 	particular subprogram based on the value of argv[0].  Also included
 *	is a little program invoked when the crunched binary is called via
 *	its EXECNAME.  This one prints out the list of compiled-in binaries,
 *	or calls one of them based on argv[1].   This allows the testing of
 *	the crunched binary without creating all the links.
 */

#include <sys/param.h>
#include <stdio.h>
#include <string.h>

__RCSID("$MirOS: src/usr.bin/crunchgen/crunched_main.c,v 1.3 2007/02/18 03:43:06 tg Exp $");

static const struct stub {
	const char *name;
	int (*f)(int, char **, char **);
} entry_points[NUMS];

static int crunched_main(int, char **, char **);
static int crunched_usage(void);

extern char *__progname;
extern char __progname_storage[NAME_MAX + 1];

int
main(int argc, char *argv[], char **envp)
{
	char *slash;
	const struct stub *ep;

	if (argv == NULL || argv[0] == NULL || *argv[0] == '\0')
		return (crunched_usage());

	slash = strrchr(argv[0], '/');
	strlcpy(__progname_storage, slash ? slash + 1 : argv[0],
	    sizeof (__progname_storage));
	__progname = __progname_storage;

	for (ep = entry_points; ep->name != NULL; ep++)
		if (!strcmp(__progname, ep->name))
			break;

	if (ep->name)
		return (ep->f(argc, argv, envp));

	fprintf(stderr, "%s: %s not compiled in\n", EXECNAME, __progname);
	return (crunched_usage());
}

static int
crunched_main(int argc, char **argv, char **envp)
{
	if (argc <= 1)
		return (crunched_usage());

	return (main(--argc, ++argv, envp));
}

static int
crunched_usage(void)
{
	int 	columns, len;
	const struct stub *ep;

	fprintf(stderr,
	    "Usage: %s <prog> <args> ..., where <prog> is one of:\n",
	    EXECNAME);
	columns = 0;
	for (ep = entry_points; ep->name != NULL; ep++) {
		len = strlen(ep->name) + 1;
		if (columns + len < 80)
			columns += len;
		else {
			fprintf(stderr, "\n");
			columns = len;
		}
		fprintf(stderr, " %s", ep->name);
	}
	fprintf(stderr, "\n");
	return (1);
}
