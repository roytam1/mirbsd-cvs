/* $MirOS: src/usr.bin/oldroff/tbl/tm.c,v 1.2 2006/10/03 19:51:11 tg Exp $ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
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

/* tm.c: split numerical fields */

# include "t..c"
__SCCSID("@(#)tm.c	4.3 (Berkeley) 4/18/91");
__RCSID("$MirOS: src/usr.bin/oldroff/tbl/tm.c,v 1.2 2006/10/03 19:51:11 tg Exp $");

char *
maknew(str)
	char *str;
{
	/* make two numerical fields */
	int c;
	char *p, *q, *ba, *dpoint;
	p = str;
	for (ba= 0; c = *str; str++)
		if (c == '\\' && *(str+1)== '&')
			ba=str;
	str=p;
	if (ba==0)
		{
		for (dpoint=0; *str; str++)
			{
			if (*str=='.' && !ineqn(str,p) &&
				(str>p && digit(*(str-1)) ||
				digit(*(str+1))))
					dpoint=str;
			}
		if (dpoint==0)
			for(; str>p; str--)
			{
			if (digit( * (str-1) ) && !ineqn(str, p))
				break;
			}
		if (!dpoint && p==str) /* not numerical, don't split */
			return(0);
		if (dpoint) str=dpoint;
		}
	else
		str = ba;
	p =str;
	if (exstore ==0 || exstore >exlim)
		{
		exstore = chspace();
		exlim= exstore+MAXCHS;
		}
	q = exstore;
	while (*exstore++ = *str++);
	*p = 0;
	return(q);
	}
ineqn (s, p)
	char *s, *p;
{
/* true if s is in a eqn within p */
int ineq = 0, c;
while (c = *p)
	{
	if (s == p)
		return(ineq);
	p++;
	if ((ineq == 0) && (c == delim1))
		ineq = 1;
	else
	if ((ineq == 1) && (c == delim2))
		ineq = 0;
	}
return(0);
}
