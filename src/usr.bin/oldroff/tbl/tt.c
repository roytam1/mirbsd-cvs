/* $MirOS: src/usr.bin/oldroff/tbl/tt.c,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $ */

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

/* tt.c: subroutines for drawing horizontal lines */

# include "t..c"
__SCCSID("@(#)tt.c	4.3 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

ctype(il, ic)
{
if (instead[il])
	return(0);
if (fullbot[il])
	return(0);
il = stynum[il];
return(style[il][ic]);
}
min(a,b)
{
return(a<b ? a : b);
}
fspan(i,c)
{
c++;
return(c<ncol && ctype(i,c)=='s');
}
lspan(i,c)
{
int k;
if (ctype(i,c) != 's') return(0);
c++;
if (c < ncol && ctype(i,c)== 's') 
	return(0);
for(k=0; ctype(i,--c) == 's'; k++);
return(k);
}
ctspan(i,c)
{
int k;
c++;
for(k=1; c<ncol && ctype(i,c)=='s'; k++)
	c++;
return(k);
}
tohcol(ic)
{
			if (ic==0)
				fprintf(tabout, "\\h'|0'");
			else
				fprintf(tabout, "\\h'(|\\n(%du+|\\n(%du)/2u'", ic+CLEFT, ic+CRIGHT-1);
}
allh(i)
{
/* return true if every element in line i is horizontal */
/* also at least one must be horizontl */
int c, one, k;
if (fullbot[i]) return(1);
for(one=c=0; c<ncol; c++)
	{
	k = thish(i,c);
	if (k==0) return(0);
	if (k==1) continue;
	one=1;
	}
return(one);
}
thish(i,c)
{
	int t;
	char *s;
	struct colstr *pc;
	if (c<0)return(0);
	if (i<0) return(0);
	t = ctype(i,c);
	if (t=='_' || t == '-')
		return('-');
	if (t=='=')return('=');
	if (t=='^') return(1);
	if (fullbot[i] )
		return(fullbot[i]);
	if (t=='s') return(thish(i,c-1));
	if (t==0) return(1);
	pc = &table[i][c];
	s = (t=='a' ? pc->rcol : pc->col);
	if (s==0 || (point(s) && *s==0))
		return(1);
	if (vspen(s)) return(1);
	if (t=barent( s))
		return(t);
	return(0);
}
