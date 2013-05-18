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
static char sccsid[] = "@(#)inv5.c	4.4 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdio.h>

recopy (ft, fb, fa, nhash)
FILE *ft, *fb, *fa;
{
	/* copy fb (old hash items/pointers) to ft (new ones) */
	int n, i, iflong;
	long getl();
	int getw();
	int *hpt_s;
	long *hpt_l;
	long k, lp;
	if (fa==NULL)
	{
		err("No old pointers",0);
		return;
	}
	fread(&n, sizeof(n), 1, fa);
	fread(&iflong, sizeof(iflong), 1, fa);
	if (iflong)
	{
		hpt_l = (long *) calloc(sizeof(*hpt_l), n+1);
		n =fread(hpt_l, sizeof(*hpt_l), n, fa);
	}
	else
	{
		hpt_s =  (int *) calloc(sizeof(*hpt_s), n+1);
		n =fread(hpt_s, sizeof(*hpt_s), n, fa);
	}
	if (n!= nhash)
		fprintf(stderr, "Changing hash value to old %d\n",n);
	fclose(fa);
	for(i=0; i<n; i++)
	{
		if (iflong) {
			lp = hpt_l[i];
			fseek(fb, lp, 0);
			while ( (k= getl(fb) ) != -1)
				fprintf(ft, "%04d %06ld\n",i,k);
		} else {
			lp = hpt_s[i];
			fseek(fb, lp, 0);
			while ( (k= getw(fb) ) != -1)
				fprintf(ft, "%04d %06ld\n",i,k);
		}
	}
	fclose(fb);
	return(n);
}
