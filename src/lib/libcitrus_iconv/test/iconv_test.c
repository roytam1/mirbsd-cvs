/* $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $ */

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
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <iconv.h>
#include <stdio.h>

unsigned char sb[512] = "fAbianBHello, world!", db[512] = "aaaaaaaaaaaaaaaaaa";

int
main(int argc, char **argv)
{
	iconv_t i;
	size_t ss, ds, rv;
	unsigned char *sp, *dp;

	sb[1]=0xE4;
	sb[6]=0;

	i = iconv_open("UTF-8", "ISO-8859-1");
	if (i == (iconv_t)-1)
		perror("iconv_open");

#if 0
	ss = sizeof (sb);
#else
	ss = strlen(sb);
#endif
	ds = sizeof (db);

	sp = sb;
	dp = db;

	rv = iconv(i, (char **)&sp, &ss, (char **)&dp, &ds);

	if (rv == (size_t)-1)
		perror("iconv");

	printf("iconv: %d invalid, new src=%d dst=%d\ndump:", rv, ss, ds);
	for (sp = db; sp <= dp; ++sp)
		printf(" %02X", *sp & 0xFF);
	*dp = '\0';
	printf("\nString: %s\n", db);

	if (iconv_close(i))
		perror("iconv_close");

	dp = db;
	if (*dp++ != 'f')
		return (1);
	if (*dp++ != 0xC3)
		return (1);
	if (*dp++ != 0xA4)
		return (1);
	return (strcmp(dp, "bian"));
}
