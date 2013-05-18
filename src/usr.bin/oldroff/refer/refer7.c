/* $MirOS$ */

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
static char sccsid[] = "@(#)refer7.c	4.5 (Berkeley) 4/18/91";
#endif /* not lint */

#include <stdlib.h>

#include "refer..c"

int newr[250];

chkdup(tag)
char *tag;
{
	int i;

	for(i = 1; i <= refnum; i++) {
		if (strcmp(reftable[i], tag)==0)
			return(i);
	}
	reftable[refnum+1] = rtp;
	if (refnum >= NRFTBL)
		err("too many references (%d) for table", refnum);
	strcpy(rtp, tag);
	while (*rtp++);
	if (rtp > reftext + NRFTXT)
		err("reference pointers too long (%d)", rtp-reftext);
	return(0);
}

dumpold()
{
	FILE *fi;
	int c, g1 = 0, nr = 1;

	if (!endpush)
		return;
	if (fo != NULL) {
		fclose(fo);
		fo = NULL;
	}
	if (sort) {
		char comm[100];
		sprintf(comm, "sort -f %s -o %s", tfile, tfile);
		system(comm);
	}
	fi = fopen(tfile, "r");
	if (fi == NULL)
		return;
	flout();
	fprintf(ftemp, ".]<\n");
	while ((c = getc(fi)) > 0) {
		if (c == '\n') {
			nr++;
			g1 = 0;
		}
		if (c == sep)
			c = '\n';
		if (c == FLAG) {
			/* make old-new ref number table */
			char tb[20];
			char *s = tb;
			while ((c = getc(fi)) != FLAG)
				*s++ = c;
			*s = 0;
			if (g1++ == 0)
				newr[atoi(tb)] = nr;
#if EBUG
			fprintf(stderr,
				"nr %d assigned to atoi(tb) %d\n",nr,atoi(tb));
# endif
			fprintf(ftemp,"%d", nr);
			continue;
		}
		putc(c, ftemp);
	}
	fclose(fi);
#ifndef TF
	unlink(tfile);
#endif
	fprintf(ftemp, ".]>\n");
}

recopy (fnam)
char *fnam;
{
	int c;
	int *wref = NULL;
	int wcnt = 0;
	int wsize = 50;
	int finalrn;
	char sig[MXSIG];

	wref = (int *)calloc((unsigned)wsize, (unsigned)sizeof(int));
	fclose(ftemp);
	ftemp = fopen(fnam, "r");
	if (ftemp == NULL) {
		fprintf(stderr, "Can't reopen %s\n", fnam);
		exit(1);
	}
	while ((c = getc(ftemp)) != EOF) {
		if (c == FLAG) {
			char tb[10];
			char *s = tb;
			while ((c = getc(ftemp)) != FLAG)
				*s++ = c;
			*s = 0;
			/*
			 * If sort was done, permute the reference number
			 * to obtain the final reference number, finalrn.
			 */
			if (sort)
				finalrn = newr[atoi(tb)];
			else
				finalrn = atoi(tb);
			if ((++wcnt > wsize) && 
			 ((wref=realloc(wref,(wsize+=50)*sizeof(int)))==NULL)){
				fprintf(stderr, "Ref condense out of memory.");
				exit(1);
			}
			wref[wcnt-1] = finalrn;
			if ((c = getc(ftemp)) == AFLAG) 
				continue;
			wref[wcnt] = 0;
			condense(wref,wcnt,sig);
			wcnt = 0;
			printf("%s", sig);
		}
		putchar(c);
	}
	fclose(ftemp);
	unlink(fnam);
}

/*
 * sort and condense referance signals when they are placed in
 * the text. Viz, the signal 1,2,3,4 is condensed to 1-4 and signals
 * of the form 5,2,9 are converted to 2,5,9
 */
condense(wref, wcnt, sig)
int	*wref;
int	wcnt;
char	*sig;
{
	register int i = 0;
	char wt[4];
	extern int wswap();

	qsort(wref, wcnt, sizeof(int), wswap);
	sig[0] = 0;
	while (i < wcnt) {
		sprintf(wt,"%d",wref[i]);
		strcat(sig,wt);
		if ((i+2 < wcnt) && (wref[i] == (wref[i+2] - 2))) {
			while (wref[i] == (wref[i+1] - 1))
				i++;
			strcat(sig, "-");
		} else if (++i < wcnt)
			strcat(sig,",\\|");
	}
}

wswap(iw1, iw2)
register int *iw1,*iw2;
{
	return(*iw1 - *iw2);
}
