/* $MirOS: src/usr.bin/oldroff/tbl/t..c,v 1.3 2006/10/03 19:51:10 tg Exp $ */

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

#define T__C_SCCSID	"@(#)t..c	4.5 (Berkeley) 4/18/91"
#define T__C_RCSID	"$MirOS: src/usr.bin/oldroff/tbl/t..c,v 1.3 2006/10/03 19:51:10 tg Exp $"

/* t..c : external declarations */

# include "stdio.h"
# include "ctype.h"

# define MAXLIN 200
# define MAXHEAD 100
# define MAXCOL 20
# define MAXCHS 2000
# define MAXRPT 100
# define CLLEN 10
# define SHORTLINE 4
extern int nlin, ncol, iline, nclin, nslin;
extern int style[MAXHEAD][MAXCOL];
extern int ctop[MAXHEAD][MAXCOL];
extern char font[MAXHEAD][MAXCOL][2];
extern char csize[MAXHEAD][MAXCOL][4];
extern char vsize[MAXHEAD][MAXCOL][4];
extern char cll[MAXCOL][CLLEN];
extern int stynum[];
extern int F1, F2;
extern int lefline[MAXHEAD][MAXCOL];
extern int fullbot[];
extern char *instead[];
extern int expflg;
extern int ctrflg;
extern int evenflg;
extern int evenup[];
extern int boxflg;
extern int dboxflg;
extern int linsize;
extern int tab;
extern int pr1403;
extern int linsize, delim1, delim2;
extern int allflg;
extern int textflg;
extern int left1flg;
extern int dummyflg;
extern int rightl;
struct colstr {char *col, *rcol;};
/* FIXME: kludge for seeing if somebody stuffed a char into col or rcol. */
# define tx(a) ((int)(a)>0 && (int)(a)<128)
extern struct colstr *table[];
extern char *cspace, *cstore;
extern char *chspace();
extern char *exstore, *exlim;
extern int sep[];
extern int used[], lused[], rused[];
extern int linestop[];
extern int leftover;
extern char *last, *ifile;
extern int texname;
extern int texct, texmax;
extern char texstr[];
extern int linstart;


extern FILE *tabin, *tabout;
# define CRIGHT 80
# define CLEFT 40
# define CMID 60
# define S1 31
# define S2 32
# define TMP 38
# define SF 35
# define SL 34
# define LSIZE 33
# define SIND 37
# define SVS 36
/* this refers to the relative position of lines */
# define LEFT 1
# define RIGHT 2
# define THRU 3
# define TOP 1
# define BOT 2
