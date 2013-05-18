/*-
 * Copyright (c) 2004, 2005, 2007, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
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
 *-
 * Generate a dump of what leap seconds userspace currently knows of,
 * for use within an environment where tzdata is not available.
 */

#include <err.h>
#include <stdio.h>
#include <time.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

static const char preamble[] =
"/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n"
"\n"
"#include <sys/time.h>\n"
"\n"
"__RCSID(\"From: $MirOS$\");\n"
"\n"
"static time_t _leaps[] = {\n";

static const char epilogue[] =
"	/* spare for config(8) */\n"
"	0,\n"
"	0,\n"
"	0,\n"
"	0,\n"
"	0,\n"
"	0,\n"
"	/* last one must be 0 */\n"
"	0,\n"
"	/* past last one must be -1 */\n"
"	(time_t)-1\n"
"};\n"
"\n"
"const time_t *\n"
"mirtime_getleaps(void)\n"
"{\n"
"	return (_leaps);\n"
"}\n";

int
main(int argc, char *argv[])
{
	time_t *lp;

	lp = mirtime_getleaps();

	fputs(preamble, stdout);
	while (*lp)
		printf("\t0x%16llXLL,\n", *lp++);
	fputs(epilogue, stdout);

	return (0);
}
