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
static char sccsid[] = "@(#)hunt8.c	4.5 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include <assert.h>
#include "pathnames.h"
#define unopen(fil) {if (fil!=NULL) {fclose(fil); fil=NULL;}}

extern long indexdate, gdate();
extern FILE *iopen();
runbib (s)
char *s;
{
	/* make a file suitable for fgrep */
	char tmp[200];
	sprintf(tmp, "%s '%s' > '%s.ig'", _PATH_MKEY,s,s);
	system(tmp);
}

makefgrep(indexname)
char *indexname;
{
	FILE *fa, *fb;
	if (ckexist(indexname, ".ig"))
	{
		/* existing gfrep -type index */
# if D1
		fprintf(stderr, "found fgrep\n");
# endif
		fa = iopen(indexname, ".ig");
		fb = iopen(indexname, "");
		if (gdate(fb)>gdate(fa))
		{
			if (fa!=NULL)
				fclose(fa);
			runbib(indexname);
			fa= iopen(indexname, ".ig");
		}
		indexdate = gdate(fa);
		unopen(fa); 
		unopen(fb);
	}
	else
		if (ckexist(indexname, ""))
		{
			/* make fgrep */
# if D1
			fprintf(stderr, "make fgrep\n");
# endif
			runbib(indexname);
			time(&indexdate);
		}
		else /* failure */
		return(0);
	return(1); /* success */
}

ckexist(s, t)
char *s, *t;
{
	char fnam[100];
	strcpy (fnam, s);
	strcat (fnam, t);
	return (access(fnam, 04) != -1);
}

FILE *
iopen(s, t)
char *s, *t;
{
	char fnam[100];
	FILE *f;
	strcpy (fnam, s);
	strcat (fnam, t);
	f = fopen (fnam, "r");
	if (f == NULL)
	{
		err("Missing expected file %s", fnam);
		exit(1);
	}
	return(f);
}
