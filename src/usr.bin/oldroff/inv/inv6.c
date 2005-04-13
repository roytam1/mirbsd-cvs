/* $MirOS: src/usr.bin/oldroff/inv/inv6.c,v 1.1.7.1 2005/03/06 16:56:01 tg Exp $ */

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
static char sccsid[] = "@(#)inv6.c	4.3 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include <assert.h>

whash(ft, fa, fb, nhash, iflong, ptotct, phused)
FILE *fa, *fb, *ft;
int nhash, *phused;
long *ptotct;
{
	char line[100];
	int hash = 0, hused = 0;
	long totct = 0L;
	int ct = 0;
	long point;
	long opoint = -1;
	int m;
	int k; 
	long lp;
	long *hpt;
	int *hfreq;

	hpt = (long *) calloc (nhash+1, sizeof(*hpt));
	assert (hpt != NULL);
	hfreq = (int *) calloc (nhash, sizeof(*hfreq));
	assert (hfreq != NULL);
	hpt[0] = 0;
	lp= 0;
	while (fgets(line, 100, ft))
	{
		totct++;
		sscanf(line, "%d %ld", &k, &point);
		if (hash < k)
		{
			hused++;
			if (iflong) putl(-1L, fb); 
			else putw(-1, fb);
			hfreq[hash]=ct;
			while (hash<k)
			{
				hpt[++hash] = lp;
				hfreq[hash] = 0;
			}
			hpt[hash] = lp += iflong? sizeof(long) : sizeof(int);
			opoint= -1;
			ct=0;
		}
		if (point!=opoint)
		{
			if (iflong)
				putl(opoint=point, fb);
			else
				putw( (int)(opoint=point), fb);
			lp += iflong? sizeof(long) : sizeof(int);
			ct++;
		}
	}
	if (iflong) putl(-1L, fb); 
	else putw(-1,fb);
	while (hash<nhash)
		hpt[++hash]=lp;
	fwrite(&nhash, sizeof(nhash), 1, fa);
	fwrite(&iflong, sizeof(iflong), 1, fa);
	fwrite(hpt, sizeof(*hpt), nhash, fa);
	fwrite (hfreq, sizeof(*hfreq), nhash, fa);
	*ptotct = totct;
	*phused = hused;
}

putl(ll, f)
long ll;
FILE *f;
{
	putw(ll, f);
}

long
getl(f)
FILE *f;
{
	return(getw(f));
}
