/* $MirOS$ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 * Redistributions of source code and documentation must retain
 * the above copyright notice, this list of conditions and the
 * following disclaimer.  Redistributions in binary form must
 * reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * All advertising materials mentioning features or use of this
 * software must display the following acknowledgement:
 *   This product includes software developed or owned by
 *   Caldera International, Inc.
 *
 * Neither the name of Caldera International, Inc. nor the names
 * of other contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE
 * LIABLE FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef lint
static char sccsid[] = "@(#)lookbib.c	4.8 (Berkeley) 6/2/92";
#endif /* not lint */

#include <stdio.h>
#include <ctype.h>
#include "pathnames.h"

main(argc, argv)	/* look in biblio for record matching keywords */
int argc;
char **argv;
{
	FILE *fp, *hfp, *fopen(), *popen();
	char s[BUFSIZ], hunt[64];
	int instructions = 1;

	if (argc > 1 && strcmp(argv[1],"-n") == 0)
	{
		argv++;
		argc--;
		instructions = 0;
	}
	if (argc == 1 || argc > 2)
	{
		fputs("Usage:  lookbib database\n",
			stderr);
		fputs("\tfinds citations specified on standard input\n",
			stderr);
		exit(1);
	}
	if (!isatty(fileno(stdin)))
		fp = stdin;
	else if ((fp = fopen(_PATH_TTY, "r")) == NULL)
	{
		perror(_PATH_TTY);
		exit(1);
	}
	(void)snprintf(s, BUFSIZ, "%s.ia", argv[1]);
	if (access(s, 0) == -1) {
		(void)snprintf (s, BUFSIZ, "%s", argv[1]);
		if (access(s, 0) == -1) {
			perror(s);
			fprintf(stderr, "\tNeither index file %s.ia ", s);
			fprintf(stderr, "nor reference file %s found\n", s);
			exit(1);
		}
	}
	(void)snprintf(hunt, 64, "%s %s", _PATH_HUNT, argv[1]);

	if (instructions && isatty(fileno(fp)))
	{
		fprintf(stderr, "Instructions? ");
		fgets(s, BUFSIZ, fp);
		if (*s == 'y')
			instruct();
	}
   again:
	fprintf(stderr, "> ");
	if (fgets(s, BUFSIZ, fp))
	{
		if (*s == '\n')
			goto again;
		if ((hfp = popen(hunt, "w")) == NULL)
		{
			perror("lookbib: hunt");
			exit(1);
		}
		map_lower(s);
		fputs(s, hfp);
		pclose(hfp);
		goto again;
	}
	fclose(fp);
	fprintf(stderr, "EOT\n");
	exit(0);
}

map_lower(s)		/* map string s to lower case */
char *s;
{
	for ( ; *s; ++s)
		if (isupper(*s))
			*s = tolower(*s);
}

instruct()
{
	fputs("\nType keywords (such as author and date) after the > prompt.\n",
		stderr);
	fputs("References with those keywords are printed if they exist;\n",
		stderr);
	fputs("\tif nothing matches you are given another prompt.\n",
		stderr);
	fputs("To quit lookbib, press CTRL-d after the > prompt.\n\n",
		stderr);
}
