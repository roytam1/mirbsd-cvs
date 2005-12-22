/* $MirOS: src/usr.bin/oldroff/inv/inv2.c,v 1.1.7.1 2005/03/06 16:56:01 tg Exp $ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004, 2005
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
static char sccsid[] = "@(#)inv2.c	4.2 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include <assert.h>
#define LINESIZ 1250

newkeys (outf, inf, recf, nhash, fd, iflong)
FILE *outf, *inf, *recf, *fd;
int *iflong;
{
	/* reads key lines from inf; hashes and writes on outf;
	 * writes orig key on recf, records pointer on outf too.
	 * format of outf is : hash code space record pointer
	 */

	long lp, ftell();
	long ld = 0; 
	int ll = 0, lt = 0;
	char line[LINESIZ];
	char key[30], bkeys[40];
	char *p, *s;
	char *keyv[500];
	int i, nk, ndoc = 0, more = 0, c;

	lp = ftell (recf);
	while (fgets(line, LINESIZ, inf))
	{
		p = line;
		while (*p != '\t') p++;
		*p++ =0;
		fputs(line, recf);
		if (fd)
		{
			sprintf(bkeys, ";%ld", ld);
			ll = strlen(p);
			lt = strlen(bkeys);
			fputs(bkeys, recf);
			sprintf(bkeys, ",%d", ll);
			lt += strlen(bkeys);
			fputs(bkeys, recf);
			ld += ll;
			fputs(p, fd);
		}
		putc('\n',recf);
		for(s=p; *s; s++);
		if (*--s == '\n')
		{
			more=0;
			*s=0;
		}
		else
			more=1;
		assert (fd==0 || more==0);
		nk = getargs(p, keyv);
		if (more)
			nk--;
		for(i=0; i<nk; i++)
			fprintf(outf,"%04d %06ld\n",hash(keyv[i])%nhash, lp);
# if D1
		for(i=0; i<nk; i++)
			printf("key %s hash %d\n",keyv[i],hash(keyv[i])%nhash);
# endif
		if (more) /* allow more than LINESIZ keys */
		{
			strcpy(key, keyv[nk]);
			for(s=key; *s; s++);
			while ( (c=getc(inf)) != '\n')
			{
				if (c != ' ')
				{
					*s++ = c;
					continue;
				}
				*s=0;
				if (s>key)
					fprintf(outf, "%04d %06ld\n",hash(key)%nhash, lp);
				s = key;
			}
		}
		lp += (strlen(line)+lt+1);
		ndoc++;
	}
	*iflong = (lp>=65536L);
	if (sizeof(int)>2) *iflong=1; /* force long on VAX */
	fclose(recf);
	return(ndoc);
}

trimnl(p)
char *p;
{
	while (*p) p++;
	p--;
	if (*p == '\n') *p=0;
}
