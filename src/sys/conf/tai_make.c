/*-
 * Copyright (c) 2004, 2005, 2007
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
 *-
 * Generate dump of leap secons.
 */

#include <sys/types.h>
#include <sys/taitime.h>
#include <err.h>
#include <stdio.h>
#include <time.h>

__RCSID("$MirOS: src/sys/lib/libkern/tai_make.c,v 1.5 2007/02/07 20:43:27 tg Exp $");

static const char preamble[] =
"/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n\n"
"#include <sys/types.h>\n"
"#include <sys/taitime.h>\n\n"
"__RCSID(\"From: $MirOS: src/sys/lib/libkern/tai_make.c,v 1.5 2007/02/07 20:43:27 tg Exp $\");\n\n"
"static tai64_t _leaps[] = {\n";

static const char epilogue[] =
/* spare for config(8) */
"\t0,\n"
"\t0,\n"
"\t0,\n"
"\t0,\n"
"\t0,\n"
"\t0,\n"

/* last one must be 0 */
"\t0,\n"
/* all bits to 1, for config(8) as marker */
"\t-1LL\n"

/* rest of the C file */
"};\n\n"
"tai64_t *\ntai_leaps(void)\n"
"{\n"
"	return (_leaps);\n"
"}\n";

int
main(int argc, char *argv[])
{
	int64_t *t;

	if (sizeof (int64_t) != sizeof (tai64_t))
		errx(1, "tai64_t is not int64_t");

	t = (int64_t *)tai_leaps();
	if (*t == 0)
		errx(1, "leap second table empty");

	fputs(preamble, stdout);
	while (*t)
		printf("\t0x%16llXLL,\n", *t++);
	fputs(epilogue, stdout);

	return (0);
}
