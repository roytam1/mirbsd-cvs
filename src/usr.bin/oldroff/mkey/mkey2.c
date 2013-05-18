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
__SCCSID("@(#)mkey2.c	4.3 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

#include <stdio.h>
#include <ctype.h>
#define MAXLINE 500

static int eof = 0;
static long lp, lim;
static int alph, used, prevc;
static char *p, key[20];

dofile(f, name)
FILE *f;
char *name;
{
	/* read file f & spit out keys & ptrs */

	char line[MAXLINE], *s;
	extern int keycount;
	int c;
	long grec(char *, FILE *, size_t);
	extern int wholefile;
	alph=used=prevc=eof=0;

	lp=0;
	if (wholefile==0)
		while (lim = grec(line,f,MAXLINE))
		{
# if D1
			fprintf(stderr, "line: /%s",line);
# endif
			used=alph=0;
			p = key;
			for(s=line; (c= *s) && (used<keycount); s++)
				chkey(c, name);
			lp += lim;
			if (used) putchar('\n');
		}
	else
	{
		p=key;
		used=alph=0;
		while ( (c=getc(f)) != EOF && used<keycount)
			chkey (c, name);
		if (used) putchar('\n');
	}
	fclose(f);
}

outkey( ky, lead, trail)
char *ky;
{
	extern int minlen;
	int n;
	n = strlen(ky);
	if (n<minlen) return (0);
	if (n<3)
	{
		if (trail == '.') return(0);
		if (mindex(".%,!#$%&'();+:*", lead)!=0) return(0);
	}
	if (isdigit(ky[0]))
		if (ky[0] != '1' || ky[1] != '9' || n!= 4) return(0);
	if (common(ky))
		return(0);
	return(1);
}

long
grec (s, f, l)
char *s;
FILE *f;
size_t l;
{
	char tm[200];
	int curtype = 0;
	long len = 0L, tlen = 0L;
	extern int wholefile;
	extern char *iglist;

	if (eof) return(0);
	*s = 0;
	while (fgets(tm, 200, f))
	{
		tlen += strlen(tm);
		if (tm[0] == '%' || tm[0] == '.')
			curtype = tm[1];
		if (tlen < MAXLINE && mindex(iglist,curtype)==0)
			strlcat(s, tm, l);
		len = tlen;
		if (wholefile==0 && tm[0] == '\n')
			return(len);
		if (wholefile>0 && len >= MAXLINE)
		{
			fseek (f, 0L, 2);
			return(ftell(f));
		}
	}
	eof=1;
	return(s[0] ? len : 0L);
}

char *
trimnl(ln)
char *ln;
{
	register char *p = ln;
	while (*p) p++;
	p--;
	if (*p == '\n') *p=0;
	return(ln);
}

chkey (int c, char *name)
{
	extern int labels;
	extern int wholefile;

	if (isalpha(c) || isdigit(c))
	{
		if (alph++ < 6)
			*p++ = c;
	}
	else
	{
		*p = 0;
		for(p=key; *p; p++)
			*p |= 040;
		if (outkey(p=key,prevc,c))
		{
			if (used==0)
			{
				if (labels)
				{
					if (wholefile==0)
						printf("%s:%ld,%ld\t", name, lp, lim);
					else
						printf("%s\t", name);
				}
			}
			else
				putchar(' ');
			fputs(key, stdout);
			used++;
		}
		prevc=c;
		alph=0;
	}
}
