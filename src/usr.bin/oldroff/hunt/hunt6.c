/* $MirOS: src/usr.bin/oldroff/hunt/hunt6.c,v 1.1.7.1 2005/03/06 16:56:01 tg Exp $ */

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
static char sccsid[] = "@(#)hunt6.c	4.4 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include <assert.h>
#define TXTLEN 1000

char *outbuf = 0;
extern char *soutput;
extern int soutlen, iflong;
extern long indexdate;

baddrop(master, nf, fc, nitem, qitem, rprog, full)
unsigned *master;
FILE *fc;
char *qitem[], *rprog;
{
	/* checks list of drops for real bad drops; finds items with "deliv" */
	union ptr {
		unsigned *a; 
		long *b; 
	} umaster;
	int i, g, j, need, got, na, len;
	long lp;
	char res[100], *ar[50], output[TXTLEN];
	extern int colevel, reached;
	
	if (iflong)
		umaster.b = (long *) master;
	else
		umaster.a = master;
# if D1
	if (iflong)
		fprintf(stderr,"in baddrop, nf %d umaster %ld %ld %ld\n",
			nf, umaster.b[0], umaster.b[1], umaster.b[2]);
	else
		fprintf(stderr,"in baddrop, nf %d umaster %d %d %d\n",
			nf, umaster.a[0], umaster.a[1], umaster.a[2]);
# endif
	for (i=g=0; i<nf; i++)
	{
		lp = iflong ? umaster.b[i] : umaster.a[i];
# if D1
		if (iflong)
			fprintf(stderr, "i %d umaster %lo lp %lo\n",
				i, umaster.b[i], lp);
		else
			fprintf(stderr, "i %d umaster %o lp %lo\n",
				i, umaster.a[i], lp);
# endif
		fseek (fc, lp, 0);
		fgets( res, 100, fc);
# if D1
		fprintf(stderr, "tag %s", res);
# endif
		if (!auxil(res,output))
		{
			char *s; 
			int c;
# if D1
			fprintf(stderr, "not auxil try rprog %c\n",
				rprog? 'y': 'n');
# endif
			for(s=res; c= *s; s++)
				if (c == ';' || c == '\n')
				{
					*s=0; 
					break;
				}
			len = rprog ?
			corout (res, output, rprog, 0, TXTLEN) :
			findline (res, output, TXTLEN, indexdate);
		}
# if D1
		assert (len <TXTLEN);
		fprintf(stderr,"item %d of %d, tag %s len %d output\n%s\n..\n",
			i, nf, res, len, output);
# endif
		if (len==0)
			continue;
		need = colevel ? reached : nitem;
		na=0;
		ar[na++] = "fgrep";
		ar[na++] = "-r";
		ar[na++] = "-n";
		ar[na++] = (char *) need;
		ar[na++] = "-i";
		ar[na++] = output;
		ar[na++] = (char *) len;
		for(j=0; j<nitem; j++)
			ar[na++] = qitem[j];
# ifdef D1
		fprintf(stderr, "calling fgrep len %d ar[4] %s %o %d \n",
			len,ar[4],ar[5],ar[6]);
# endif
		if (fgrep(na, ar)==0)
		{
# ifdef D1
			fprintf(stderr, "fgrep found it\n");
# endif
			if (iflong)
				umaster.b[g++] = umaster.b[i];
			else
				umaster.a[g++] = umaster.a[i];
			if (full >= g)
				if (soutput==0)
					fputs(output, stdout);
				else
					strcpy (soutput, output);
		}
# ifdef D1
		fprintf(stderr, "after fgrep\n");
# endif
	}
	return(g);
}

auxil( res, output)
char *res, *output;
{
	extern FILE *fd;
	long lp, c; 
	int len;
	if (fd==0)return(0);
	while (c = *res++) 
	{
		if (c == ';')
		{
			sscanf(res, "%ld,%d", &lp, &len);
			fseek (fd, lp, 0);
			fgets(output, len, fd);
			return(1);
		}
	}
	return(0);
}
