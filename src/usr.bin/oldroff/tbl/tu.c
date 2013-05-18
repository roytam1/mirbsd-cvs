/* $MirOS: src/usr.bin/oldroff/tbl/tu.c,v 1.1.7.1 2005/03/06 16:56:03 tg Exp $ */

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

/* tu.c: draws horizontal lines */

# include "t..c"
__SCCSID("@(#)tu.c	4.4 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

makeline(i,c,lintype)
{
int cr, type, shortl;
type = thish(i,c);
if (type==0) return;
cr=c;
shortl = (table[i][c].col[0]=='\\');
if (c>0 && !shortl && thish(i,c-1) == type)return;
if (shortl==0)
	for(cr=c; cr < ncol && (ctype(i,cr)=='s'||type==thish(i,cr)); cr++);
else
	for(cr=c+1; cr<ncol && ctype(i,cr)=='s'; cr++);
drawline(i, c, cr-1, lintype, 0, shortl);
}
fullwide(i, lintype)
{
int cr, cl;
if (!pr1403)
	fprintf(tabout, ".nr %d \\n(.v\n.vs \\n(.vu-\\n(.sp\n", SVS);
cr= 0;
while (cr<ncol)
	{
	cl=cr;
	while (i>0 && vspand(prev(i),cl,1))
		cl++;
	for(cr=cl; cr<ncol; cr++)
		if (i>0 && vspand(prev(i),cr,1))
			break;
	if (cl<ncol)
	drawline(i,cl,(cr<ncol?cr-1:cr),lintype,1,0);
	}
fprintf(tabout, "\n");
if (!pr1403)
	fprintf(tabout, ".vs \\n(%du\n", SVS);
}

drawline(i, cl, cr, lintype, noheight, shortl)
{
	char *exhr, *exhl, *lnch;
	int lcount, ln, linpos, oldpos, nodata;
lcount=0;
exhr=exhl= "";
switch(lintype)
	{
	case '-': lcount=1;break;
	case '=': lcount = pr1403? 1 : 2; break;
	case SHORTLINE: lcount=1; break;
	}
if (lcount<=0) return;
nodata = cr-cl>=ncol || noheight || allh(i);
	if (!nodata)
		fprintf(tabout, "\\v'-.5m'");
for(ln=oldpos=0; ln<lcount; ln++)
	{
	linpos = 2*ln - lcount +1;
	if (linpos != oldpos)
		fprintf(tabout, "\\v'%dp'", linpos-oldpos);
	oldpos=linpos;
	if (shortl==0)
	{
	tohcol(cl);
	if (lcount>1)
		{
		switch(interv(i,cl))
			{
			case TOP: exhl = ln==0 ? "1p" : "-1p"; break;
			case BOT: exhl = ln==1 ? "1p" : "-1p"; break;
			case THRU: exhl = "1p"; break;
			}
		if (exhl[0])
		fprintf(tabout, "\\h'%s'", exhl);
		}
	else if (lcount==1)
		{
		switch(interv(i,cl))
			{
			case TOP: case BOT: exhl = "-1p"; break;
			case THRU: exhl = "1p"; break;
			}
		if (exhl[0])
		fprintf(tabout, "\\h'%s'", exhl);
		}
	if (lcount>1)
		{
		switch(interv(i,cr+1))
			{
			case TOP: exhr = ln==0 ? "-1p" : "+1p"; break;
			case BOT: exhr = ln==1 ? "-1p" : "+1p"; break;
			case THRU: exhr = "-1p"; break;
			}
		}
	else if (lcount==1)
		{
		switch(interv(i,cr+1))
			{
			case TOP: case BOT: exhr = "+1p"; break;
			case THRU: exhr = "-1p"; break;
			}
		}
	}
	else
		fprintf(tabout, "\\h'|\\n(%du'", cl+CLEFT);
	fprintf(tabout, "\\s\\n(%d",LSIZE);
	if (linsize)
		fprintf(tabout, "\\v'-\\n(%dp/6u'", LSIZE);
	if (shortl)
		fprintf(tabout, "\\l'|\\n(%du'", cr+CRIGHT);
	else
	{
	lnch = "\\(ul";
	if (pr1403)
		lnch = lintype==2 ? "=" : "\\(ru";
	if (cr+1>=ncol)
		fprintf(tabout, "\\l'|\\n(TWu%s%s'", exhr,lnch);
	else
		fprintf(tabout, "\\l'(|\\n(%du+|\\n(%du)/2u%s%s'", cr+CRIGHT,
			cr+1+CLEFT, exhr, lnch);
	}
	if (linsize)
		fprintf(tabout, "\\v'\\n(%dp/6u'", LSIZE);
	fprintf(tabout, "\\s0");
	}
if (oldpos!=0)
	fprintf(tabout, "\\v'%dp'", -oldpos);
if (!nodata)
	fprintf(tabout, "\\v'+.5m'");
}
getstop()
{
int i,c,k,junk, stopp;
stopp=1;
for(i=0; i<MAXLIN; i++)
	linestop[i]=0;
for(i=0; i<nlin; i++)
	for(c=0; c<ncol; c++)
		{
		k = left(i,c,&junk);
		if (k>=0 && linestop[k]==0)
			linestop[k]= ++stopp;
		}
if (boxflg || allflg || dboxflg)
	linestop[0]=1;
}
left(i,c, lwidp)
	int *lwidp;
{
int kind, li, lj;
	/* returns -1 if no line to left */
	/* returns number of line where it starts */
	/* stores into lwid the kind of line */
*lwidp=0;
kind = lefdata(i,c);
if (kind==0) return(-1);
if (i+1<nlin)
if (lefdata(next(i),c)== kind) return(-1);
while (i>=0 && lefdata(i,c)==kind)
	i=prev(li=i);
if (prev(li)== -1) li=0;
*lwidp=kind;
for(lj= i+1; lj<li; lj++)
	if (instead[lj] && strcmp(instead[lj], ".TH")==0)
		return(li);
for(i= i+1; i<li; i++)
	if (fullbot[i])
		li=i;
return(li);
}
lefdata(i,c)
{
int ck;
if (i>=nlin) i=nlin-1;
if (ctype(i,c) == 's')
	{
	for(ck=c; ctype(i,ck)=='s'; ck--);
	if (thish(i,ck)==0)
		return(0);
	}
i =stynum[i];
i = lefline[i][c];
if (i>0) return(i);
if (dboxflg && c==0) return(2);
if (allflg)return(1);
if (boxflg && c==0) return(1);
return(0);
}
next(i)
{
while (i+1 <nlin)
	{
	i++;
	if (!fullbot[i] && !instead[i]) break;
	}
return(i);
}
prev(i)
{
while (--i >=0  && (fullbot[i] || instead[i]))
	;
return(i);
}
