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
static char sccsid[] = "@(#)refer2.c	4.4 (Berkeley) 4/18/91";
#endif /* not lint */

#include "refer..c"
#define NFLD 30
#define TLEN 512

extern FILE *in;
char one[ANSLEN];
int onelen = ANSLEN;
extern char usedir[];

doref(line1)
char *line1;
{
	char buff[QLEN], dbuff[3*QLEN];
	char answer[ANSLEN], temp[TLEN], line[BUFSIZ];
	char *p, **sr, *flds[NFLD], *r;
	int stat, nf, nr, query = 0, alph, digs;

   again:
	buff[0] = dbuff[0] = 0;
	if (biblio && Iline == 1 && line1[0] == '%')
		strcat(dbuff, line1);
	while (input(line)) {		/* get query */
		Iline++;
		if (prefix(".]", line))
			break;
		if (biblio && line[0] == '\n')
			break;
		if (biblio && line[0] == '%' && line[1] == *convert)
			break;
		if (control(line[0]))
			query = 1;
		strcat(query ? dbuff : buff, line);
		if (strlen(buff) > QLEN)
			err("query too long (%d)", strlen(buff));
		if (strlen(dbuff) > 3 * QLEN)
			err("record at line %d too long", Iline-1);
	}
	if (biblio && line[0] == '\n' && feof(in))
		return;
	if (strcmp(buff, "$LIST$\n")==0) {
		assert (dbuff[0] == 0);
		dumpold();
		return;
	}
	answer[0] = 0;
	for (p = buff; *p; p++) {
		if (isupper(*p))
			*p |= 040;
	}
	alph = digs = 0;
	for (p = buff; *p; p++) {
		if (isalpha(*p))
			alph++;
		else
			if (isdigit(*p))
				digs++;
			else {
				*p = 0;
				if ((alph+digs < 3) || common(p-alph)) {
					r = p-alph;
					while (r < p)
						*r++ = ' ';
				}
				if (alph == 0 && digs > 0) {
					r = p-digs;
					if (digs != 4 || atoi(r)/100 != 19) {
						while (r < p)
							*r++ = ' ';
					}
				}
				*p = ' ';
				alph = digs = 0;
			}
	}
	one[0] = 0;
	if (buff[0]) {	/* do not search if no query */
		for (sr = rdata; sr < search; sr++) {
			temp[0] = 0;
			corout(buff, temp, "hunt", *sr, TLEN);
			assert(strlen(temp) < TLEN);
			if (strlen(temp)+strlen(answer) > BUFSIZ)
				err("Accumulated answers too large",0);
			strcat(answer, temp);
			if (strlen(answer)>BUFSIZ)
				err("answer too long (%d)", strlen(answer));
			if (newline(answer) > 0)
				break;
		}
	}
	assert(strlen(one) < ANSLEN);
	assert(strlen(answer) < ANSLEN);
	if (buff[0])
		switch (newline(answer)) {
		case 0:
			fprintf(stderr, "No such paper: %s\n", buff);
			return;
		default:
			fprintf(stderr, "Too many hits: %s\n", trimnl(buff));
			choices(answer);
			p = buff;
			while (*p != '\n')
				p++;
			*++p = 0;
		case 1:
			if (endpush)
				if (nr = chkdup(answer)) {
					if (bare < 2) {
						nf = tabs(flds, one);
						nf += tabs(flds+nf, dbuff);
						assert(nf < NFLD);
						putsig(nf,flds,nr,line1,line,0);
					}
					return;
				}
			if (one[0] == 0)
				corout(answer, one, "deliv", usedir, QLEN);
			break;
		}
	assert(strlen(buff) < QLEN);
	assert(strlen(one) < ANSLEN);
	nf = tabs(flds, one);
	nf += tabs(flds+nf, dbuff);
	assert(nf < NFLD);
	refnum++;
	if (sort)
		putkey(nf, flds, refnum, keystr);
	if (bare < 2)
		putsig(nf, flds, refnum, line1, line, 1);
	else
		flout();
	putref(nf, flds);
	if (biblio && line[0] == '\n')
		goto again;
	if (biblio && line[0] == '%' && line[1] == *convert)
		fprintf(fo, "%s%c%s", convert+1, sep, line+3);
}

newline(s)
char *s;
{
	int k = 0, c;

	while (c = *s++)
		if (c == '\n')
			k++;
	return(k);
}

choices(buff)
char *buff;
{
	char ob[BUFSIZ], *p, *r, *q, *t;
	int nl;

	for (r = p = buff; *p; p++) {
		if (*p == '\n') {
			*p++ = 0;
			corout(r, ob, "deliv", usedir, BUFSIZ);
			nl = 1;
			for (q = ob; *q; q++) {
				if (nl && (q[0]=='.'||q[0]=='%') && q[1]=='T') {
					q += 3;
					for (t = q; *t && *t != '\n'; t++)
						;
					*t = 0;
					fprintf(stderr, "%.70s\n", q);
					q = 0;
					break;
				}
				nl = *q == '\n';
			}
			if (q)
				fprintf(stderr, "??? at %s\n",r);
			r=p;
		}
	}
}

control(c)
{
	if (c == '.')
		return(1);
	if (c == '%')
		return(1);
	return(0);
}
