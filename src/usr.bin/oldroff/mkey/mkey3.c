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
static char sccsid[] = "@(#)mkey3.c	4.3 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>
#include "pathnames.h"

#define COMNUM 500
#define COMTSIZE 997

char *comname = _PATH_EIGN;
static int cgate = 0;
extern char *comname;
int comcount = 100;
static char cbuf[COMNUM*9];
static char *cwds[COMTSIZE];
static char *cbp;

common (s)
char *s;
{
	if (cgate==0) cominit();
	return (c_look(s, 1));
}

cominit()
{
	int i;
	FILE *f;
	cgate=1;
	f = fopen(comname, "r");
	if (f==NULL) return;
	cbp=cbuf;
	for(i=0; i<comcount; i++)
	{
		if (fgets(cbp, 15, f)==NULL)
			break;
		trimnl(cbp);
		c_look (cbp, 0);
		while (*cbp++);
	}
	fclose(f);
}

c_look (s, fl)
char *s;
{
	int h;
	h = hash(s) % (COMTSIZE);
	while (cwds[h] != 0)
	{
		if (strcmp(s, cwds[h])==0)
			return(1);
		h = (h+1) % (COMTSIZE);
	}
	if (fl==0)
		cwds[h] = s;
	return(0);
}
