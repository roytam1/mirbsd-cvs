/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 *-
 * Generate dump of leap secons.
 */

#include <sys/param.h>
#include <err.h>
#include <stdio.h>
#include <time.h>

__RCSID("$MirOS$");

static const char preamble[] =
"/* AUTOMATICALLY GENERATED - DO NOT EDIT! */\n\n"
"#include <sys/types.h>\n"
"#include <lib/libkern/taitime.h>\n\n"
"static tai64_t _leaps[] = {\n";

static const char epilogue[] =
"\t0,\n"
"\t0,\n"
"\t0,\n"
"\t0,\n"
"\t0\n"
"};\n\n"
"tai64_t *\n_tai_leaps(void)\n"
"{\n"
"	return _leaps;\n"
"}\n";


int
main(int argc, char *argv[])
{
	int64_t *t;

	if (sizeof(int64_t) != sizeof(tai64_t))
		errx(1, "tai64_t is not int64_t!");

	if ((t = (int64_t *)tai_leaps()) == NULL)
		errx(1, "Cannot get leap seconds!");

	if (!(*t))
		errx(1, "Leap second table empty!");

	printf("%s", preamble);
	while (*t) {
		printf("\t0x%16llXLL,\n", *t);
		++t;
	}
	printf("%s", epilogue);

	return 0;
}
