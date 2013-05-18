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

#include <sys/cdefs.h>
__SCCSID("@(#)sortbib.c	4.6 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "pathnames.h"

#define BUF BUFSIZ
#define MXFILES 16

char *tempfile;			/* temporary file for sorting keys */
char *keystr = "AD";		/* default sorting on author and date */
int multauth = 0;		/* by default sort on senior author only */
int oneauth;			/* has there been author in the record? */

main(argc, argv)	/* sortbib: sort bibliographic database in place */
int argc;
char *argv[];
{
	FILE *fp[MXFILES], *tfp, *fopen();
	int i;
	void onintr();
	int mkstemp();

	if (argc == 1)		/* can't use stdin for seeking anyway */
	{
		puts("Usage:  sortbib [-sKEYS] database [...]");
		puts("\t-s: sort by fields in KEYS (default is AD)");
		exit(1);
	}
	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 's')
	{
		keystr = argv[1]+2;
		eval(keystr);		/* evaluate A+ for multiple authors */
		argv++; argc--;
	}
	if (argc > MXFILES+1)	/* too many open file streams */
	{
		fprintf(stderr,
		"sortbib: More than %d databases specified\n", MXFILES);
		exit(1);
	}
	for (i = 1; i < argc; i++)		/* open files in arg list */
		if ((fp[i-1] = fopen(argv[i], "r")) == NULL)
			error(argv[i]);
	if (signal(SIGINT,SIG_IGN) != SIG_IGN)	/* remove if interrupted */
		signal(SIGINT, onintr);
	tempfile = strdup(_PATH_TMPS);
	if ((tfp = fdopen(mkstemp(tempfile), "w")) == NULL)
		error(tempfile);

	for (i = 0; i < argc-1; i++)		/* read keys from bib files */
		sortbib(fp[i], tfp, i);
	fclose(tfp);
	deliver(fp, tfp);	/* do disk seeks and read from biblio files */
	unlink(tempfile);
	exit(0);
}

int rsmode = 0;		/* record separator: 1 = null line, 2 = bracket */

sortbib(fp, tfp, i)	/* read records, prepare list for sorting */
FILE *fp, *tfp;
int i;
{
	long offset, lastoffset = 0, ftell();	/* byte offsets in file */
	int length, newrec, recno = 0;		/* reclen, new rec'd?, number */
	char line[BUF], fld[4][BUF];		/* one line, the sort fields */

	/* measure byte offset, then get new line */
	while (offset = ftell(fp), fgets(line, BUF, fp))
	{
		if (recno == 0)		/* accept record w/o initial newline */
			newrec = 1;
		if (line[0] == '\n')	/* accept null line record separator */
		{
			if (!rsmode)
				rsmode = 1;	/* null line mode */
			if (rsmode == 1)
				newrec = 1;
		}
		if (line[0] == '.' && line[1] == '[')	/* also accept .[ .] */
		{
			if (!rsmode)
				rsmode = 2;	/* bracket pair mode */
			if (rsmode == 2)
				newrec = 1;
		}
		if (newrec)		/* by whatever means above */
		{
			newrec = 0;
			length = offset - lastoffset;	/* measure rec len */
			if (length > BUF*8)
			{
				fprintf(stderr,
				"sortbib: record %d longer than %d (%d)\n",
					recno, BUF*8, length);
				exit(1);
			}
			if (recno++)			/* info for sorting */
			{
				fprintf(tfp, "%d %ld %d : %s %s %s %s\n",
					i, lastoffset, length,
					fld[0], fld[1], fld[2], fld[3]);
				if (ferror(tfp))
					error(tempfile);
			}
			*fld[0] = *fld[1] = *fld[2] = *fld[3] = 0;
			oneauth = 0;		/* reset number of authors */
			lastoffset = offset;	/* save for next time */
		}
		if (line[0] == '%')	/* parse out fields to be sorted */
			parse(line, fld);
	}
	offset = ftell(fp);		/* measure byte offset at EOF */
	length = offset - lastoffset;	/* measure final record length */
	if (length > BUF*8)
	{
		fprintf(stderr, "sortbib: record %d longer than %d (%d)\n",
			recno, BUF*8, length);
		exit(1);
	}
	if (line[0] != '\n')		/* ignore null line just before EOF */
	{
		fprintf(tfp, "%d %ld %d : %s %s %s %s\n",
			i, lastoffset, length,
			fld[0], fld[1], fld[2], fld[3]);
		if (ferror(tfp))
			error(tempfile);	/* disk error in /tmp */
	}
}

deliver(fp, tfp)	/* deliver sorted entries out of database(s) */
FILE *fp[], *tfp;
{
	char str[BUF], buff[BUF*8];	/* for tempfile & databases */
	char cmd[80];			/* for using system sort command */
	long int offset;
	int i, length;

	/* when sorting, ignore case distinctions; tab char is ':' */
	snprintf(cmd, 80, "sort -ft: +1 %s -o %s", tempfile, tempfile);
	if (system(cmd) == 127)
		error("sortbib");
	tfp = fopen(tempfile, "r");
	while (fgets(str, sizeof(str), tfp))
	{
		/* get file pointer, record offset, and length */
		if (sscanf(str, "%d %ld %d :", &i, &offset, &length) != 3)
			error("sortbib: sorting error");
		/* seek to proper disk location in proper file */
		if (fseek(fp[i], offset, 0) == -1)
			error("sortbib");
		/* read exactly one record from bibliography */
		if (fread(buff, sizeof(*buff), length, fp[i]) == 0)
			error("sortbib");
		/* add newline between unseparated records */
		if (buff[0] != '\n' && rsmode == 1)
			putchar('\n');
		/* write record buffer to standard output */
		if (fwrite(buff, sizeof(*buff), length, stdout) == 0)
			error("sortbib");
	}
}

parse(line, fld)	/* get fields out of line, prepare for sorting */
char line[];
char fld[][BUF];
{
	char wd[8][BUF/4];
	int n, i, j;

	for (i = 0; i < 8; i++)		/* zap out old strings */
		*wd[i] = 0;
	n = sscanf(line, "%s %s %s %s %s %s %s %s",
		wd[0], wd[1], wd[2], wd[3], wd[4], wd[5], wd[6], wd[7]);
	for (i = 0; i < 4; i++)
	{
		if (wd[0][1] == keystr[i])
		{
			if (wd[0][1] == 'A')
			{
				if (oneauth && !multauth)	/* no repeat */
					break;
				else if (oneauth)		/* mult auths */
					strlcat(fld[i], "~~", BUF);
				if (!endcomma(wd[n-2]))		/* surname */
					strlcat(fld[i], wd[n-1], BUF);
				else {				/* jr. or ed. */
					strlcat(fld[i], wd[n-2], BUF);
					n--;
				}
				strlcat(fld[i], " ", BUF);
				for (j = 1; j < n-1; j++)
					strlcat(fld[i], wd[j], BUF);
				oneauth = 1;
			}
			else if (wd[0][1] == 'D')
			{
				strlcat(fld[i], wd[n-1], BUF);	/* year */
				if (n > 2)
					strlcat(fld[i], wd[1], BUF);	/* month */
			}
			else if (wd[0][1] == 'T' || wd[0][1] == 'J')
			{
				j = 1;
				if (article(wd[1]))	/* skip article */
					j++;
				for (; j < n; j++)
					strlcat(fld[i], wd[j], BUF);
			}
			else  /* any other field */
				for (j = 1; j < n; j++)
					strlcat(fld[i], wd[j], BUF);
		}
		/* %Q quorporate or queer author - unreversed %A */
		else if (wd[0][1] == 'Q' && keystr[i] == 'A')
			for (j = 1; j < n; j++)
				strlcat(fld[i], wd[j], BUF);
	}
}

article(str)		/* see if string contains an article */
char *str;
{
	if (strcmp("The", str) == 0)	/* English */
		return(1);
	if (strcmp("A", str) == 0)
		return(1);
	if (strcmp("An", str) == 0)
		return(1);
	if (strcmp("Le", str) == 0)	/* French */
		return(1);
	if (strcmp("La", str) == 0)
		return(1);
	if (strcmp("Der", str) == 0)	/* German */
		return(1);
	if (strcmp("Die", str) == 0)
		return(1);
	if (strcmp("Das", str) == 0)
		return(1);
	if (strcmp("El", str) == 0)	/* Spanish */
		return(1);
	if (strcmp("Den", str) == 0)	/* Scandinavian */
		return(1);
	return(0);
}

eval(keystr)		/* evaluate key string for A+ marking */
char keystr[];
{
	int i, j;

	for (i = 0, j = 0; keystr[i]; i++, j++)
	{
		if (keystr[i] == '+')
		{
			multauth = 1;
			i++;
		}
		keystr[j] = keystr[i];
	}
	keystr[j] = 0;
}

error(s)		/* exit in case of various system errors */
char *s;
{
	perror(s);
	exit(1);
}

void
onintr()		/* remove tempfile in case of interrupt */
{
	fprintf(stderr, "\nInterrupt\n");
	unlink(tempfile);
	exit(1);
}

endcomma(str)
char *str;
{
	int n;

	n = strlen(str) - 1;
	if (str[n] == ',')
	{
		str[n] = 0;
		return(1);
	}
	return(0);
}
